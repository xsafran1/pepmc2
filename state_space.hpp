#ifndef STATE_SPACE_HPP
#define STATE_SPACE_HPP

#include "model.hpp"
#include "paramset.hpp"

#include <boost/optional.hpp>
#include <boost/range.hpp>
#include <boost/functional/hash.hpp>
#include <vector>

template <typename T>
class state_space
{
public:
	typedef T value_type;
	typedef model<T> model_type;

	state_space()
	{
	}

	template <typename ThresholdIter>
	state_space(model_type const & model, ThresholdIter thresholds)
		: m_model(model)
	{
		for (std::size_t i = 0; i < m_model.dims(); ++i, ++thresholds)
		{
			m_thresholds.push_back(std::vector<value_type>(boost::begin(*thresholds), boost::end(*thresholds)));
			std::sort(m_thresholds.back().begin(), m_thresholds.back().end());
		}
	}

	// TODO: make this private
	model_type m_model;
	std::vector<std::vector<value_type> > m_thresholds;
	paramset<std::size_t> m_init;
	paramset<std::size_t> m_final;

	struct vertex_descriptor
	{
		std::vector<std::size_t> coords;

		vertex_descriptor()
		{
		}

		explicit vertex_descriptor(std::size_t i)
			: coords(i)
		{
		}

		bool empty() const
		{
			return coords.empty();
		}

		friend std::ostream & operator<<(std::ostream & out, vertex_descriptor const & v)
		{
			if (v.coords.empty())
				out << "(";
			else
				out << "(" << v.coords[0];
			for (std::size_t i = 1; i < v.coords.size(); ++i)
				out << ", " << v.coords[i];
			return out << ")";
		}

		friend bool operator==(vertex_descriptor const & lhs, vertex_descriptor const & rhs)
		{
			return lhs.coords == rhs.coords;
		}

		friend bool operator<(vertex_descriptor const & lhs, vertex_descriptor const & rhs)
		{
			return lhs.coords < rhs.coords;
		}

		friend std::size_t hash_value(vertex_descriptor const & v)
		{
			return boost::hash_value(v.coords);
		}
	};

	template <typename State>
	class real_state
	{
	public:
		real_state(state_space const & ss, State state)
			: m_ss(ss), m_state(state)
		{
		}

		value_type operator[](std::size_t i) const
		{
			return m_ss.m_thresholds[i][m_state[i]];
		}

	private:
		state_space const & m_ss;
		State m_state;
	};

	template <typename State, typename Param>
	value_type value(std::size_t dim, State const & state, Param const & param) const
	{
		return m_model.value(dim, real_state<State const &>(*this, state), param);
	}

	bool final(vertex_descriptor const & v) const
	{
		for (std::size_t i = 0; i < m_final.regions().size(); ++i)
		{
			bool res = true;

			std::vector<std::pair<std::size_t, std::size_t> > const & box = m_final.regions()[i].box;
			for (std::size_t j = 0; res && j < box.size(); ++j)
			{
				if (box[j].first > v.coords[j] || v.coords[j] >= box[j].second)
					res = false;
			}

			if (res)
				return true;
		}
		return false;
	}

	class init_enumerator
	{
	public:
		init_enumerator(state_space const & g)
			: m_g(g), m_region_index(0), m_value(g.m_model.dims())
		{
			this->reset_region();
		}

		bool valid() const
		{
			return m_region_index < m_g.m_init.regions().size();
		}

		void next()
		{
			bool carry = true;
			for (std::size_t i = 0; carry && i < m_g.m_init.regions()[m_region_index].box.size(); ++i)
			{
				++m_value.coords[i];
				carry = m_value.coords[i] >= m_g.m_init.regions()[m_region_index].box[i].second;
				if (carry)
					m_value.coords[i] = m_g.m_init.regions()[m_region_index].box[i].first;
			}

			if (carry)
			{
				++m_region_index;
				this->reset_region();
			}
		}

		vertex_descriptor get() const
		{
			return m_value;
		}

	private:
		void reset_region()
		{
			if (m_region_index < m_g.m_init.regions().size())
			{
				for (std::size_t i = 0; i < m_g.m_init.regions()[m_region_index].box.size(); ++i)
					m_value.coords[i] = m_g.m_init.regions()[m_region_index].box[i].first;
			}
		}

		state_space const & m_g;
		std::size_t m_region_index;
		vertex_descriptor m_value;
	};

	class out_edge_enumerator
	{
	public:
		out_edge_enumerator(state_space const & g, vertex_descriptor const & source)
			: m_g(&g), m_source(source), m_dim(0), m_up(false)
		{
			this->find_next();
		}

		void reset()
		{
			m_dim = 0;
			m_up = false;
			this->find_next();
		}

		vertex_descriptor const & source() const
		{
			return m_source;
		}

		vertex_descriptor target() const
		{
			vertex_descriptor res = m_source;
			if (m_up)
				++res.coords[m_dim];
			else
				--res.coords[m_dim];
			return res;
		}

		template <typename Tag>
		void paramset_intersect(paramset<T, Tag> & p) const
		{
			BOOST_ASSERT(m_dim < m_source.coords.size());

			paramset<T, Tag> removed = std::move(p);
			p.clear();

			std::vector<bool> shifts(m_g->m_model.dims());
			shifts[m_dim] = m_up;

			std::vector<value_type> pt(m_g->m_model.dims());

			bool carry = false;
			while (!carry)
			{
				for (std::size_t i = 0; i < pt.size(); ++i)
					pt[i] = m_g->m_thresholds[i][m_source.coords[i] + shifts[i]];

				m_g->m_model.paramset_transfer(removed, p, pt, m_dim, m_up);
				if (removed.empty())
					break;

				carry = true;
				for (std::size_t i = 0; carry && i < shifts.size(); ++i)
				{
					if (i == m_dim)
						continue;

					carry = shifts[i];
					shifts[i] = true;
				}
			}
		}

		bool valid() const
		{
			return m_dim < m_source.coords.size();
		}

		void next()
		{
			BOOST_ASSERT(m_dim < m_source.coords.size());

			if (m_up)
				++m_dim;
			m_up = !m_up;
			this->find_next();
		}

		state_space const * m_g;
		vertex_descriptor m_source;
		std::size_t m_dim;
		bool m_up;

	private:
		void find_next()
		{
			while (
				m_dim < m_source.coords.size()
				&& ((!m_up && m_source.coords[m_dim] == 0)
					|| (m_up && m_source.coords[m_dim] + 2 == m_g->m_thresholds[m_dim].size())
					)
				)
			{
				if (m_up)
					++m_dim;
				m_up = !m_up;
			}
		}
	};

	std::size_t dims() const
	{
		return m_model.dims();
	}

	template <typename Paramset>
	void remove_nontransient(Paramset & p_down, Paramset & p_up, vertex_descriptor const & v, std::size_t dim) const
	{
		std::vector<value_type> pt(m_model.dims());
		std::vector<bool> shifts(m_model.dims());

		bool carry = false;
		while (!carry)
		{
			for (std::size_t i = 0; i < pt.size(); ++i)
				pt[i] = m_thresholds[i][v.coords[i] + shifts[i]];

			m_model.fix_paramsets(p_down, p_up, pt, dim);

			if (p_down.empty() && p_up.empty())
				break;

			carry = true;
			for (std::size_t i = 0; carry && i < shifts.size(); ++i)
			{
				carry = shifts[i];
				shifts[i] = true;
			}
		}
	}

	template <typename Paramset>
	void self_loop(vertex_descriptor const & v, Paramset & p) const
	{
		for (std::size_t dim = 0; dim < m_model.dims(); ++dim)
		{
			Paramset p_down = p;
			Paramset p_up = p;
			this->remove_nontransient(p_down, p_up, v, dim);
			p.set_difference(p_down);
			p.set_difference(p_up);
		}
	}

	struct literal_proposition
	{
		std::size_t dim;
		value_type value;
		bool negate;
	};

	// conjunctive normal form
	struct proposition
	{
		typedef literal_proposition literal_type;
		std::vector<std::vector<literal_proposition> > m_clauses;
	};

	bool valid(proposition const & prop, vertex_descriptor const & v) const
	{
		for (std::size_t i = 0; i < prop.m_clauses.size(); ++i)
		{
			bool valid = false;
			for (std::size_t j = 0; !valid && j < prop.m_clauses[i].size(); ++j)
			{
				if (prop.m_clauses[i][j].negate)
				{
					valid = m_thresholds[prop.m_clauses[i][j].dim][v.coords[prop.m_clauses[i][j].dim]] >= prop.m_clauses[i][j].value;
				}
				else
				{
					valid = m_thresholds[prop.m_clauses[i][j].dim][v.coords[prop.m_clauses[i][j].dim]] < prop.m_clauses[i][j].value;
				}
			}

			if (!valid)
				return false;
		}
		return true;
	}

	void refine_thresholds(std::size_t amount)
	{
		std::vector<std::vector<value_type> > new_thresholds;
		for (std::size_t i = 0; i < m_thresholds.size(); ++i)
		{
			std::vector<value_type> const & thr = m_thresholds[i];
			std::vector<value_type> v(1, thr[0]);

			for (std::size_t j = 1; j < thr.size(); ++j)
			{
				for (std::size_t k = 0; k < amount + 1; ++k)
					v.push_back(thr[j-1] + (thr[j] - thr[j-1])/(amount+1)*(k+1));
			}

			new_thresholds.push_back(v);
		}

		m_thresholds = new_thresholds;

		for (std::size_t i = 0; i < m_init.regions().size(); ++i)
		{
			for (std::size_t j = 0; j < m_init.regions()[i].box.size(); ++j)
			{
				m_init.regions()[i].box[j].first *= amount + 1;
				m_init.regions()[i].box[j].second *= amount + 1;
			}
		}

		for (std::size_t i = 0; i < m_final.regions().size(); ++i)
		{
			for (std::size_t j = 0; j < m_final.regions()[i].box.size(); ++j)
			{
				m_final.regions()[i].box[j].first *= amount + 1;
				m_final.regions()[i].box[j].second *= amount + 1;
			}
		}
	}

	friend std::ostream & operator<<(std::ostream & o, state_space const & v)
	{
		return o << v.m_model;
	}
};

#endif

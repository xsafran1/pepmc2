#ifndef LRPARSER_PARSING_ACTION_HPP
#define LRPARSER_PARSING_ACTION_HPP

#include <cstdlib>
#include <ostream>

#include <boost/assert.hpp>
#include <boost/none.hpp>
#include <boost/variant.hpp>

template <typename Nonterminal, typename ReduceAction>
class parsing_action
{
public:
	typedef Nonterminal nonterminal_type;
	typedef ReduceAction reduce_action_type;

	struct shift_t
	{
		explicit shift_t(std::size_t target)
			: target(target)
		{
		}
		
		std::size_t target;

		friend std::ostream & operator<<(std::ostream & o, shift_t const & v)
		{
			return o << "shift(" << v.target << ")";
		}
	};

	struct reduce_t
	{
		reduce_t(reduce_action_type const & action, nonterminal_type const & base, std::size_t symcount)
			: action(action), base(base), symcount(symcount)
		{
		}

		reduce_action_type action;
		nonterminal_type base;
		std::size_t symcount;

		friend std::ostream & operator<<(std::ostream & o, reduce_t const & v)
		{
			return o << "reduce";
		}
	};

	parsing_action()
	{
	}

	parsing_action(boost::none_t const &)
	{
	}

	parsing_action(shift_t const & action)
		: m_action(action)
	{
	}

	parsing_action(reduce_t const & action)
		: m_action(action)
	{
	}

	int which() const
	{
		return m_action.which();
	}

	shift_t const & shift() const
	{
		BOOST_ASSERT(this->which() == 1);
		return boost::get<shift_t>(m_action);
	}

	reduce_t const & reduce() const
	{
		BOOST_ASSERT(this->which() == 2);
		return boost::get<reduce_t>(m_action);
	}

private:
	boost::variant<boost::none_t, shift_t, reduce_t> m_action;
};

#endif

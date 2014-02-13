#ifndef LRPARSER_TERMINAL_SET_HPP
#define LRPARSER_TERMINAL_SET_HPP

#include <set>
#include <iterator>
#include <algorithm>

template <typename Terminal>
class terminal_set
{
public:
	typedef Terminal value_type;
	typedef typename std::set<value_type>::const_iterator const_iterator;

	terminal_set()
	{
	}

	terminal_set(value_type terminal)
		: m_values(&terminal, &terminal + 1)
	{
	}

	terminal_set(value_type first, value_type last)
	{
		for (; first <= last; ++first)
			m_values.insert(first);
	}

	const_iterator begin() const { return m_values.begin(); }
	const_iterator end() const { return m_values.end(); }

	bool contains(value_type terminal) const
	{
		return m_values.find(terminal) != m_values.end();
	}

	bool empty() const
	{
		return m_values.empty();
	}

	std::size_t size() const
	{
		return m_values.size();
	}

	terminal_set & operator|=(terminal_set const & rhs)
	{
		m_values.insert(rhs.begin(), rhs.end());
		return *this;
	}

	terminal_set & operator|=(value_type const & rhs)
	{
		m_values.insert(rhs);
		return *this;
	}

	friend terminal_set operator|(terminal_set lhs, terminal_set const & rhs)
	{
		return lhs |= rhs;
	}

	friend terminal_set set_union(terminal_set const & lhs, terminal_set const & rhs)
	{
		terminal_set res;
		std::set_union(lhs.begin(), lhs.end(), rhs.begin(), rhs.end(), std::inserter(res.m_values, res.m_values.end()));
		return res;
	}

	friend terminal_set set_intersection(terminal_set const & lhs, terminal_set const & rhs)
	{
		terminal_set res;
		std::set_intersection(lhs.begin(), lhs.end(), rhs.begin(), rhs.end(), std::inserter(res.m_values, res.m_values.end()));
		return res;
	}

	friend terminal_set set_difference(terminal_set const & lhs, terminal_set const & rhs)
	{
		terminal_set res;
		std::set_difference(lhs.begin(), lhs.end(), rhs.begin(), rhs.end(), std::inserter(res.m_values, res.m_values.end()));
		return res;
	}

	friend bool operator<(terminal_set const & lhs, terminal_set const & rhs)
	{
		return lhs.m_values < rhs.m_values;
	}

private:
	std::set<value_type> m_values;
};

#endif

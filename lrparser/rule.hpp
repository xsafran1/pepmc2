#ifndef LRPARSER_RULE_HPP
#define LRPARSER_RULE_HPP

#include <cstdlib>
#include <vector>
#include <boost/variant.hpp>

#include <ostream>

// The rule must store base, since multiple rules can have the same base.
template <typename TerminalSet, typename Nonterminal, typename ReduceAction = std::size_t>
struct rule
{
	typedef TerminalSet terminal_set_type;
	typedef Nonterminal nonterminal_type;
	typedef boost::variant<terminal_set_type, nonterminal_type> symbol_type;
	typedef ReduceAction reduce_action_type;

	typedef typename std::vector<symbol_type>::const_iterator symbol_const_iterator;

	explicit rule(nonterminal_type const & base, reduce_action_type const & action = reduce_action_type())
		: m_base(base), m_reduce_action(action)
	{
	}

	friend rule & operator<<(rule & r, terminal_set_type v)
	{
		r.m_symbols.push_back(v);
		return r;
	}

	friend rule & operator<<(rule & r, nonterminal_type v)
	{
		r.m_symbols.push_back(v);
		return r;
	}

	nonterminal_type const & base() const { return m_base; }
	reduce_action_type const & reduce_action() const { return m_reduce_action; }

	symbol_const_iterator symbol_begin() const { return m_symbols.begin(); }
	symbol_const_iterator symbol_end() const { return m_symbols.end(); }
	symbol_type symbol(std::size_t i) const { return m_symbols[i]; }
	std::size_t symbol_count() const { return m_symbols.size(); }

	friend bool operator==(rule const & lhs, rule const & rhs)
	{
		if (lhs.m_base != rhs.m_base || lhs.m_symbols.size() != rhs.m_symbols.size())
			return false;

		return std::equal(lhs.m_symbols.begin(), lhs.m_symbols.end(), rhs.m_symbols.begin());
	}

	friend bool operator!=(rule const & lhs, rule const & rhs)
	{
		return !(lhs == rhs);
	}

	friend bool operator<(rule const & lhs, rule const & rhs)
	{
		return lhs.m_base < rhs.m_base
			|| (lhs.m_base == rhs.m_base && std::lexicographical_compare(lhs.m_symbols.begin(), lhs.m_symbols.end(), rhs.m_symbols.begin(), rhs.m_symbols.end()));
	}

	friend bool operator>(rule const & lhs, rule const & rhs)
	{
		return rhs < lhs;
	}

	friend bool operator<=(rule const & lhs, rule const & rhs)
	{
		return !(rhs < lhs);
	}

	friend bool operator>=(rule const & lhs, rule const & rhs)
	{
		return !(lhs < rhs);
	}

private:
	nonterminal_type m_base;
	std::vector<symbol_type> m_symbols;
	reduce_action_type m_reduce_action;
};

#endif

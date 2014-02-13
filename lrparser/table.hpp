#ifndef LRPARSER_TABLE_HPP
#define LRPARSER_TABLE_HPP

#include <cstdlib>
#include <ostream>
#include <utility>
#include <map>
#include <stdexcept>

#include <boost/variant.hpp>
#include <boost/optional.hpp>

#include "parsing_action.hpp"
#include "conflict.hpp"

template <typename TerminalSet, typename Nonterminal, typename ReduceAction>
class traits
{
public:
	typedef TerminalSet terminal_set_type;
	typedef typename terminal_set_type::value_type terminal_type;
	typedef Nonterminal nonterminal_type;
	typedef ReduceAction reduce_action_type;
	typedef parsing_action<nonterminal_type, reduce_action_type> action_type;

	void add_goto(nonterminal_type const & nonterminal, std::size_t target)
	{
		BOOST_ASSERT(m_goto_table.find(nonterminal) == m_goto_table.end());
		m_goto_table[nonterminal] = target;
	}

	void add_action(terminal_set_type const & lookahead, action_type const & action)
	{
		for (typename terminal_set_type::const_iterator ci = lookahead.begin();
			ci != lookahead.end(); ++ci)
		{
			typename std::map<terminal_type, action_type>::const_iterator prev_action = m_lookahead_action_table.find(*ci);
			if (prev_action != m_lookahead_action_table.end())
				throw conflict_error<nonterminal_type, reduce_action_type>(action, prev_action->second);
			m_lookahead_action_table.insert(std::make_pair(*ci, action));
		}
	}

	void add_action(action_type const & action)
	{
		if (m_eof_action.which() != 0)
			throw conflict_error<nonterminal_type, reduce_action_type>(action, m_eof_action);
		m_eof_action = action;
	}

	action_type action(terminal_type const & lookahead) const
	{
		typename std::map<terminal_type, action_type>::const_iterator
			ci = m_lookahead_action_table.find(lookahead);

		if (ci == m_lookahead_action_table.end())
			return boost::none;

		return ci->second;
	}

	action_type action() const
	{
		return m_eof_action;
	}

	boost::optional<std::size_t> next(nonterminal_type const & nonterminal) const
	{
		typename std::map<nonterminal_type, std::size_t>::const_iterator
			goto_ci = m_goto_table.find(nonterminal);

		if (goto_ci == m_goto_table.end())
			return boost::none;

		return goto_ci->second;
	}

private:
	std::map<nonterminal_type, std::size_t> m_goto_table;
	std::map<terminal_type, action_type> m_lookahead_action_table;
	action_type m_eof_action;
};

template <typename TerminalSet, typename Nonterminal, typename ReduceAction,
	typename StateTraits = traits<TerminalSet, Nonterminal, ReduceAction> >
class lr1_table
{
public:
	typedef TerminalSet terminal_set_type;
	typedef typename terminal_set_type::value_type terminal_type;
	typedef Nonterminal nonterminal_type;
	typedef ReduceAction reduce_action_type;

	typedef StateTraits traits_type;
	typedef typename StateTraits::action_type action_type;

	lr1_table()
		: m_accepting_state(0)
	{
	}

	void add_reduction(std::size_t state, boost::optional<terminal_type> const & lookahead,
		reduce_action_type const & action, nonterminal_type const & base, std::size_t symcount)
	{
		this->resize_states(state);
		if (lookahead)
			m_states[state].add_action(*lookahead, typename action_type::reduce_t(action, base, symcount));
		else
			m_states[state].add_action(typename action_type::reduce_t(action, base, symcount));
	}

	void add_shift(std::size_t state, terminal_set_type const & symbol, std::size_t next)
	{
		this->resize_states(state);
		m_states[state].add_action(symbol, typename action_type::shift_t(next));
	}

	void add_goto(std::size_t state, nonterminal_type const & symbol, std::size_t next)
	{
		this->resize_states(state);
		m_states[state].add_goto(symbol, next);
	}

	action_type action(std::size_t state, typename terminal_set_type::value_type const & lookahead) const
	{
		return m_states[state].action(lookahead);
	}

	action_type action(std::size_t state) const
	{
		return m_states[state].action();
	}

	boost::optional<std::size_t> next(std::size_t state, nonterminal_type const & nonterminal) const
	{
		return m_states[state].next(nonterminal);
	}

	void accepting_state(std::size_t state)
	{
		m_accepting_state = state;
	}

	std::size_t accepting_state() const
	{
		return m_accepting_state;
	}

private:
	std::vector<traits_type> m_states;

	std::size_t m_accepting_state;

	// TODO: rename
	void resize_states(std::size_t size)
	{
		if (m_states.size() < size+1)
			m_states.resize(size+1);
	}
};

#endif

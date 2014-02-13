#ifndef LRPARSER_CONFLICT_HPP
#define LRPARSER_CONFLICT_HPP

#include <exception>
#include "parsing_action.hpp"

template <typename Nonterminal, typename ReduceAction>
class conflict_error
	: public std::exception
{
public:
	typedef parsing_action<Nonterminal, ReduceAction> action_type;

	conflict_error(action_type new_action, action_type old_action)
		: m_new_action(new_action), m_old_action(old_action)
	{
	}

	~conflict_error() throw()
	{
	}

	virtual const char* what() const throw()
	{
		return "conflict";
	}

	action_type new_action() const { return m_new_action; }
	action_type old_action() const { return m_old_action; }

private:
	action_type m_new_action;
	action_type m_old_action;
};

template <typename Itemset, typename Nonterminal, typename ReduceAction>
class statetrace_conflict_error
	: public conflict_error<Nonterminal, ReduceAction>
{
public:
	typedef parsing_action<Nonterminal, ReduceAction> action_type;

	statetrace_conflict_error(action_type new_action, action_type old_action)
		: conflict_error<Nonterminal, ReduceAction>(new_action, old_action)
	{
	}

	~statetrace_conflict_error() throw()
	{
	}

	void add_state(Itemset const & itemset)
	{
		m_states.push_back(itemset);
	}

	std::vector<Itemset> m_states;
};

#endif

#ifndef LRPARSER_GENERATOR_HPP
#define LRPARSER_GENERATOR_HPP

#include <cstdlib>

#include <map>
#include <set>
#include <vector>

#include <boost/assert.hpp>
#include <boost/optional.hpp>
#include <boost/tuple/tuple.hpp>
#include <boost/tuple/tuple_comparison.hpp>

#include "grammar.hpp"
#include "first.hpp"

namespace detail {

template <typename RuleIterator, typename Terminal>
struct item
{
	typedef RuleIterator rule_iterator;
	typedef Terminal terminal_type;

	rule_iterator rule;
	std::size_t marker;
	boost::optional<terminal_type> lookahead;

	item(rule_iterator rule, std::size_t marker, boost::optional<terminal_type> const & lookahead)
		: rule(rule), marker(marker), lookahead(lookahead)
	{
	}

	friend bool operator<(item const & lhs, item const & rhs)
	{
		return boost::tie(lhs.rule, lhs.marker, lhs.lookahead) < boost::tie(rhs.rule, rhs.marker, rhs.lookahead);
	}
};

}

struct generate_lr1_tables_visitor
{
	template <typename Itemset>
	void closed_itemset(Itemset const &) const
	{
	}
};

namespace detail {

template <typename TerminalSet, typename Itemset>
void fixup_term_kernels(std::map<TerminalSet, Itemset> & term_kernels)
{
	std::map<TerminalSet, Itemset> old_res;

	for (typename std::map<TerminalSet, Itemset>::const_iterator ci = term_kernels.begin();
		ci != term_kernels.end(); ++ci)
	{
		TerminalSet distrib = ci->first;
		std::map<TerminalSet, Itemset> new_res;

		for (typename std::map<TerminalSet, Itemset>::const_iterator res_ci = old_res.begin();
			!distrib.empty() && res_ci != old_res.end(); ++res_ci)
		{
			TerminalSet subset = set_intersection(distrib, res_ci->first);
			if (!subset.empty())
			{
				new_res[subset].insert(res_ci->second.begin(), res_ci->second.end());
				new_res[subset].insert(ci->second.begin(), ci->second.end());
			}

			subset = set_difference(res_ci->first, distrib);
			if (!subset.empty())
				new_res[subset].insert(res_ci->second.begin(), res_ci->second.end());

			distrib = set_difference(distrib, res_ci->first);
		}

		old_res.swap(new_res);
		if (!distrib.empty())
			old_res[distrib].insert(ci->second.begin(), ci->second.end());
	}

	term_kernels.swap(old_res);
}

}

template <typename RuleIterator, typename Visitor, typename Table>
void generate_lr1_tables(RuleIterator first, RuleIterator last,
	typename std::iterator_traits<RuleIterator>::value_type::nonterminal_type const & root_nonterminal,
	Visitor const & visitor,
	Table & table)
{
	// TODO: Review this and optimize.

	BOOST_ASSERT(first != last);

	typedef typename std::iterator_traits<RuleIterator>::value_type rule_type;
	typedef typename rule_type::nonterminal_type nonterminal_type;
	typedef typename rule_type::terminal_set_type terminal_set_type;
	typedef typename rule_type::symbol_type symbol_type;
	typedef typename rule_type::reduce_action_type reduce_action_type;
	typedef boost::optional<terminal_set_type> lookahead_type;

	typedef first_table<terminal_set_type, nonterminal_type> fi_type;

	fi_type fi(first, last);

	typedef detail::item<RuleIterator, typename terminal_set_type::value_type> item_type;
	typedef std::map<nonterminal_type, std::vector<RuleIterator> > rule_index_type;

	rule_index_type rule_index;
	for (RuleIterator iter = first; iter != last; ++iter)
		rule_index[iter->base()].push_back(iter);

	BOOST_ASSERT(rule_index.find(root_nonterminal) != rule_index.end());

	typedef std::set<item_type> itemset_type;
	std::vector<itemset_type> states(1);
	std::map<itemset_type, std::size_t> kernels_index;

	std::vector<itemset_type> closed_states;
	std::vector<std::size_t> state_trace(1);

	itemset_type & root_itemset = states[0];
	std::vector<RuleIterator> const & root_rules = rule_index[root_nonterminal];
	for (size_t i = 0; i < root_rules.size(); ++i)
		root_itemset.insert(item_type(root_rules[i], 0, boost::none));

	for (std::size_t processed_states = 0; processed_states < states.size(); ++processed_states)
	{
		itemset_type const & current_state = states[processed_states];

		std::vector<item_type> itemlist(current_state.begin(), current_state.end());
		std::set<item_type> itemset = current_state;

		std::map<terminal_set_type, itemset_type> term_kernels;
		std::map<nonterminal_type, itemset_type> nonterm_kernels;

		for (std::size_t i = 0; i < itemlist.size(); ++i)
		{
			item_type const & item = itemlist[i];

			typename rule_type::symbol_const_iterator symbol_iter = item.rule->symbol_begin() + item.marker;
			if (symbol_iter == item.rule->symbol_end())
			{
				table.add_reduction(processed_states, item.lookahead, item.rule->reduce_action(), item.rule->base(), item.rule->symbol_count());
				continue;
			}

			if (symbol_iter->which() == 0)
			{
				terminal_set_type const & term = boost::get<terminal_set_type>(*symbol_iter);
				term_kernels[term].insert(item_type(item.rule, item.marker + 1, item.lookahead));
			}
			else
			{
				nonterminal_type const & nonterm = boost::get<nonterminal_type>(*symbol_iter);
				nonterm_kernels[nonterm].insert(item_type(item.rule, item.marker + 1, item.lookahead));

				std::vector<RuleIterator> const & rules = rule_index[nonterm];
				typename fi_type::entry const & first_entries = fi(symbol_iter + 1, item.rule->symbol_end(), item.lookahead);

				for (std::size_t j = 0; j < rules.size(); ++j)
				{
					if (first_entries.m_epsilon)
					{
						item_type item(rules[j], 0, boost::none);
						if (itemset.insert(item).second)
							itemlist.push_back(item);
					}

					for (typename terminal_set_type::const_iterator
						fi_iter = first_entries.m_terminals.begin();
						fi_iter != first_entries.m_terminals.end();
						++fi_iter)
					{
						item_type item(rules[j], 0, *fi_iter);
						if (itemset.insert(item).second)
							itemlist.push_back(item);
					}
				}
			}
		}

		closed_states.push_back(itemset);

		detail::fixup_term_kernels(term_kernels);

		visitor.closed_itemset(itemset);

		try
		{
			for (typename std::map<terminal_set_type, itemset_type>::const_iterator
				iter = term_kernels.begin();
				iter != term_kernels.end();
				++iter)
			{
				typename std::map<itemset_type, std::size_t>::const_iterator ci = kernels_index.find(iter->second);

				if (ci == kernels_index.end())
				{
					ci = kernels_index.insert(std::make_pair(iter->second, states.size())).first;
					states.push_back(iter->second);
					state_trace.push_back(processed_states);
				}

				table.add_shift(processed_states, iter->first, ci->second);
			}

			for (typename std::map<nonterminal_type, itemset_type>::const_iterator
				iter = nonterm_kernels.begin();
				iter != nonterm_kernels.end();
				++iter)
			{
				typename std::map<itemset_type, std::size_t>::const_iterator ci = kernels_index.find(iter->second);

				if (ci == kernels_index.end())
				{
					ci = kernels_index.insert(std::make_pair(iter->second, states.size())).first;
					states.push_back(iter->second);
					state_trace.push_back(processed_states);
				}

				table.add_goto(processed_states, iter->first, ci->second);
			}
		}
		catch (conflict_error<nonterminal_type, reduce_action_type> const & e)
		{
			statetrace_conflict_error<itemset_type, nonterminal_type, reduce_action_type> new_e(e.new_action(), e.old_action());

			int i = processed_states;
			while (i != 0)
			{
				new_e.add_state(closed_states[i]);
				i = state_trace[i];
			}
			new_e.add_state(closed_states[0]);

			throw new_e;
		}
	}

	boost::optional<std::size_t> final_state = table.next(0, root_nonterminal);
	if (!final_state)
	{
		table.add_goto(0, root_nonterminal, states.size());
		table.accepting_state(states.size());
	}
	else
	{
		if (table.action(*final_state).which() != 0)
			throw std::runtime_error("Accept conflict.");
		table.accepting_state(*final_state);
	}
}

template <typename RuleIterator, typename Visitor, typename Table>
void generate_lr1_tables_remapped(RuleIterator first, RuleIterator last,
	typename std::iterator_traits<RuleIterator>::value_type::nonterminal_type const & root_nonterminal,
	Visitor const & visitor,
	Table & table)
{
	typedef typename std::iterator_traits<RuleIterator>::value_type rule_type;
	typedef typename rule_type::terminal_set_type terminal_set_type;
	typedef typename rule_type::reduce_action_type reduce_action_type;

	std::vector<rule<terminal_set_type, std::size_t, reduce_action_type> > rules;
	std::size_t root = remap_grammar(first, last, std::back_inserter(rules), root_nonterminal);
	generate_lr1_tables(rules.begin(), rules.end(), root, visitor, table);
}

template <typename RuleIterator, typename Table>
void generate_lr1_tables_remapped(RuleIterator first, RuleIterator last,
	typename std::iterator_traits<RuleIterator>::value_type::nonterminal_type const & root_nonterminal,
	Table & table)
{
	generate_lr1_tables_remapped(first, last, root_nonterminal, generate_lr1_tables_visitor(), table);
}

template <typename RuleIterator, typename Table>
void generate_lr1_tables_print_trace(RuleIterator first, RuleIterator last,
	typename std::iterator_traits<RuleIterator>::value_type::nonterminal_type const & root_nonterminal,
	Table & table, std::ostream & out)
{
	typedef typename std::iterator_traits<RuleIterator>::value_type rule_type;
	typedef typename rule_type::nonterminal_type nonterminal_type;
	typedef typename rule_type::terminal_set_type terminal_set_type;
	typedef typename rule_type::terminal_set_type::value_type terminal_type;
	typedef typename rule_type::symbol_type symbol_type;
	typedef typename rule_type::reduce_action_type reduce_action_type;

	typedef std::set<detail::item<RuleIterator, terminal_type> > itemset_type;

	try
	{
		generate_lr1_tables(first, last, root_nonterminal, generate_lr1_tables_visitor(), table);
	}
	catch (statetrace_conflict_error<itemset_type, nonterminal_type, reduce_action_type> const & e)
	{
		for (std::size_t i = 0; i < e.m_states.size(); ++i)
		{
			for (typename itemset_type::const_iterator ci = e.m_states[i].begin();
				ci != e.m_states[i].end(); ++ci)
			{
				rule_type const & v = *ci->rule;

				out << v.base() << " -> ";
				if (ci->marker == 0)
					out << ". ";

				for (std::size_t i = 0; i < v.symbol_count(); ++i)
				{
					if (v.symbol(i).which() == 0)
					{
						out << '\'';
						terminal_set_type term = boost::get<terminal_set_type>(v.symbol(i));
						for (typename terminal_set_type::const_iterator ci = term.begin(); ci != term.end(); ++ci)
							out << *ci;
						out << '\'';
					}
					else
						out << boost::get<nonterminal_type>(v.symbol(i));

					if (ci->marker == i + 1)
						out << " . ";
					else
						out << ", ";
				}

				if (ci->lookahead)
					out << "(" << *ci->lookahead << ")";
				else
					out << "()";

				out << std::endl;
			}

			out << std::endl;
		}
	}
}

#endif

#ifndef LRPARSER_GRAMMAR_HPP
#define LRPARSER_GRAMMAR_HPP

#include "rule.hpp"
#include <vector>

template <typename Rule>
class grammar
{
public:
	typedef Rule rule_type;
	typedef typename rule_type::terminal_set_type terminal_set_type;
	typedef typename rule_type::nonterminal_type nonterminal_type;
	typedef typename rule_type::reduce_action_type reduce_action_type;

	typedef typename std::vector<rule_type>::iterator iterator;
	typedef typename std::vector<rule_type>::const_iterator const_iterator;
	typedef std::size_t size_type;

	rule_type & add(nonterminal_type const & base, reduce_action_type const & action = reduce_action_type())
	{
		m_rules.push_back(rule_type(base, action));
		return m_rules.back();
	}

	iterator begin() { return m_rules.begin(); }
	iterator end() { return m_rules.end(); }
	const_iterator begin() const { return m_rules.begin(); }
	const_iterator end() const { return m_rules.end(); }

	size_type size() const { return m_rules.size(); }
	bool empty() const { return m_rules.empty(); }

	void clear()
	{
		m_rules.clear();
	}

private:
	std::vector<rule_type> m_rules;
};

template <typename ForwardIterator, typename OutputIterator>
std::size_t remap_grammar(ForwardIterator first, ForwardIterator last, OutputIterator out,
	typename std::iterator_traits<ForwardIterator>::value_type::nonterminal_type const & root_nonterminal)
{
	typedef typename std::iterator_traits<ForwardIterator>::value_type rule_type;	
	typedef typename rule_type::terminal_set_type terminal_set_type;
	typedef typename rule_type::nonterminal_type nonterminal_type;
	typedef typename rule_type::reduce_action_type reduce_action_type;

	std::map<nonterminal_type, std::size_t> mapping;

	for (; first != last; ++first)
	{
		std::size_t & target = mapping[first->base()];
		if (target == 0)
			target = mapping.size();
		
		rule<terminal_set_type, std::size_t, reduce_action_type> new_rule(target, first->reduce_action());
		
		for (typename rule_type::symbol_const_iterator
			iter = first->symbol_begin();
			iter != first->symbol_end();
			++iter)
		{
			if (iter->which() == 0)
			{
				new_rule << boost::get<terminal_set_type>(*iter);
				continue;
			}

			std::size_t & target = mapping[boost::get<nonterminal_type>(*iter)];
			if (target == 0)
				target = mapping.size();
			new_rule << target;
		}

		*out++ = new_rule;
	}

	return mapping[root_nonterminal];
}

#endif

#ifndef LRPARSER_FIRST_HPP
#define LRPARSER_FIRST_HPP

#include <set>
#include <map>
#include <boost/optional.hpp>

template <typename TerminalSet, typename Nonterminal>
class first_table
{
public:
	typedef TerminalSet terminal_set_type;
	typedef typename terminal_set_type::value_type terminal_type;
	typedef Nonterminal nonterminal_type;

	struct entry
	{
		entry()
			: m_epsilon(false)
		{
		}

		bool m_epsilon;
		terminal_set_type m_terminals;
	};

	template <typename ForwardIterator>
	first_table(ForwardIterator first, ForwardIterator last)
	{
		typedef typename std::iterator_traits<ForwardIterator>::value_type rule_type;
		typedef typename rule_type::symbol_const_iterator symbol_const_iterator;

		bool done = false;
		while (!done)
		{
			done = true;
			for (ForwardIterator iter = first; iter != last; ++iter)
			{
				rule_type const & rule = *iter;

				entry & row = m_table[rule.base()];
				entry row_copy = row;
				if (this->update_row(rule.symbol_begin(), rule.symbol_end(), row_copy))
				{
					row = row_copy;
					done = false;
				}
			}
		}
	}

	template <typename SymbolIterator>
	entry operator()(SymbolIterator first, SymbolIterator last) const
	{
		entry res;
		this->update_row(first, last, res);
		return res;
	}

	template <typename SymbolIterator>
	entry operator()(SymbolIterator first, SymbolIterator last, boost::optional<terminal_type> const & lookahead) const
	{
		entry res;
		this->update_row(first, last, res);
		if (lookahead && res.m_epsilon)
		{
			res.m_terminals |= *lookahead;
			res.m_epsilon = false;
		}
		return res;
	}

	entry operator()(nonterminal_type const & nonterminal) const
	{
		typename std::map<nonterminal_type, entry>::const_iterator ci = m_table.find(nonterminal);
		return ci != m_table.end()? ci->second: entry();
	}

private:
	template <typename ForwardIterator>
	bool update_row(ForwardIterator first, ForwardIterator last, entry & row) const
	{
		std::size_t old_size = row.m_terminals.size();
		
		bool epsilon = true;
		for (; epsilon && first != last; ++first)
		{
			if (first->which() == 0)
			{
				row.m_terminals |= boost::get<terminal_set_type>(*first);
				epsilon = false;
			}
			else
			{
				entry const & other_entry = (*this)(boost::get<nonterminal_type>(*first));
				row.m_terminals |= other_entry.m_terminals;
				epsilon = other_entry.m_epsilon;
			}
		}

		if (epsilon && !row.m_epsilon)
		{
			row.m_epsilon = true;
			return true;
		}
		
		return row.m_terminals.size() != old_size;
	}

	std::map<nonterminal_type, entry> m_table;
};

#endif

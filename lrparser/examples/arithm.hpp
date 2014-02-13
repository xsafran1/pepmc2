#ifndef LRPARSER_EXAMPLES_ARITHM_HPP
#define LRPARSER_EXAMPLES_ARITHM_HPP

#include "../rule.hpp"
#include "../grammar.hpp"
#include "../generator.hpp"
#include "../parser.hpp"
#include "../table.hpp"
#include "../terminal_set.hpp"

#include <vector>
#include <stack>

class arithm_solver
{
public:
	arithm_solver()
	{
		grammar<rule_type> g;
		g.add("E") << "P";
		g.add("E", &arithm_solver::reduce_add) << "E" << '+' << "P";
		g.add("P") << "T";
		g.add("P", &arithm_solver::reduce_mul) << "P" << '*' << "T";
		g.add("T") << "N";
		g.add("T", &arithm_solver::reduce_neg) << '-' << "T";
		g.add("T") << '(' << "E" << ')';
		g.add("N", &arithm_solver::reduce_digit) << "L";
		g.add("N", &arithm_solver::reduce_lit) << "N" << "L";
		g.add("L") << terminal_set<char>('0', '9');

		generate_lr1_tables_remapped(g.begin(), g.end(), "E", m_table);
	}

	int solve(std::string const & expr) const
	{
		parse_visitor v(*this);
		parse(m_table, expr.begin(), expr.end(), boost::ref(v));
		return v.result();
	}

private:
	typedef void (arithm_solver::*action_type)(std::stack<int> &, char const *, char const *) const;
	typedef rule<terminal_set<char>, std::string, action_type> rule_type;

	struct parse_visitor
	{
		explicit parse_visitor(arithm_solver const & solver)
			: m_solver(solver)
		{
		}

		void reduce(action_type action, std::string::const_iterator first, std::string::const_iterator last)
		{
			if (action != 0)
				(m_solver.*action)(m_stack, &*first, &*first + (last - first));
		}

		int result() const
		{
			BOOST_ASSERT(m_stack.size() == 1);
			return m_stack.top();
		}

		arithm_solver const & m_solver;
		std::stack<int> m_stack;
	};

	void reduce_add(std::stack<int> & stack, char const *, char const *) const
	{
		int operand = stack.top();
		stack.pop();
		stack.top() = stack.top() + operand;
	}

	void reduce_mul(std::stack<int> & stack, char const *, char const *) const
	{
		int operand = stack.top();
		stack.pop();
		stack.top() = stack.top() * operand;
	}

	void reduce_neg(std::stack<int> & stack, char const *, char const *) const
	{
		stack.top() = -stack.top();
	}

	void reduce_lit(std::stack<int> & stack, char const * first, char const * last) const
	{
		BOOST_ASSERT(first != last);
		BOOST_ASSERT('0' <= last[-1] && last[-1] <= '9');
		stack.top() = stack.top() * 10 + (last[-1] - '0');
	}

	void reduce_digit(std::stack<int> & stack, char const * first, char const * last) const
	{
		BOOST_ASSERT(first + 1 == last);
		BOOST_ASSERT('0' <= *first && *first <= '9');
		stack.push(*first - '0');
	}

	lr1_table<terminal_set<char>, std::size_t, action_type> m_table;
};

#endif

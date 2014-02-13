#ifndef LRPARSER_PARSER_HPP
#define LRPARSER_PARSER_HPP

#include <algorithm>
#include <stack>
#include <stdexcept>

#include <boost/optional.hpp>
#include <boost/ref.hpp>

struct parse_visitor
{
	template <typename T, typename ForwardIterator>
	void reduce(T const &, ForwardIterator first, ForwardIterator last)
	{
	}
};

template <typename Table, typename ForwardIterator, typename Visitor>
void parse(Table const & table, ForwardIterator first, ForwardIterator last, Visitor visitor)
{
	typedef typename Table::terminal_set_type::value_type terminal_type;
	typedef typename Table::nonterminal_type nonterminal_type;
	typedef typename Table::action_type action_type;
	typedef typename Table::reduce_action_type reduce_action_type;

	typename boost::unwrap_reference<Visitor>::type & unwrapped_visitor = visitor;

	std::stack<std::size_t> state_stack;
	std::stack<ForwardIterator> input_stack;

	state_stack.push(0);
	input_stack.push(first);

	while (first != last) //automat?
	{
		action_type action = table.action(state_stack.top(), *first);

		switch (action.which())
		{
		case 0:
			// TODO: make this better.
			throw std::runtime_error("Unexpected token.");

		case 1:
			state_stack.push(action.shift().target);
			input_stack.push(first++);
			break;

		case 2:
			{
				typename action_type::reduce_t const & reduce = action.reduce();

				ForwardIterator input_top = input_stack.top();
				for (std::size_t i = 0; i < reduce.symcount; ++i)
				{
					state_stack.pop();
					input_top = input_stack.top();
					input_stack.pop();
				}

				boost::optional<std::size_t> next = table.next(state_stack.top(), reduce.base);
				state_stack.push(*next);
				input_stack.push(input_top);

				BOOST_ASSERT(state_stack.size() == input_stack.size());

				unwrapped_visitor.reduce(reduce.action, input_stack.top(), first);
			}
			break;
		}
	}

	while (state_stack.top() != table.accepting_state())
	{
		action_type action = table.action(state_stack.top());

		switch (action.which())
		{
		case 0:
		case 1:
			// TODO: make this better.
			throw std::runtime_error("Unexpected end of stream.");

		case 2:
			{
				typename action_type::reduce_t const & reduce = action.reduce();

				ForwardIterator input_top = input_stack.top();
				for (std::size_t i = 0; i < reduce.symcount; ++i)
				{
					state_stack.pop();
					input_top = input_stack.top();
					input_stack.pop();
				}

				boost::optional<std::size_t> next = table.next(state_stack.top(), reduce.base);
				state_stack.push(*next);
				input_stack.push(input_top);

				unwrapped_visitor.reduce(reduce.action, input_stack.top(), first);
			}
			break;
		}
	}

	BOOST_ASSERT(state_stack.size() == input_stack.size());

	state_stack.pop();
	state_stack.pop();
	if (!state_stack.empty())
		throw std::runtime_error("Unexpected end of stream.");
}

#endif

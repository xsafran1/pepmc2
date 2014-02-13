#ifndef LRPARSER_EXAMPLES_YACC_HPP
#define LRPARSER_EXAMPLES_YACC_HPP

#include "../rule.hpp"
#include "../grammar.hpp"
#include "../parser.hpp"
#include "../table.hpp"
#include "../generator.hpp"
#include "../terminal_set.hpp"

#include <stack>
#include <iostream>

class yacc_rule_extractor
{
public:
	yacc_rule_extractor()
	{
		grammar<rule_type> g;

		g.add("LITERAL", &parse_context::make_literal) << '\'' << terminal_set<char>(32, 126) << '\'';    // TODO: support for escaped characters inside literals
		g.add("ID_CHAR") << (terminal_set<char>('a', 'z') | terminal_set<char>('A', 'Z') | '_');
		g.add("WSP_CHAR") << (terminal_set<char>(' ') | '\t' | '\n');

		g.add("WSP");
		g.add("WSP") << "WSP" << "WSP_CHAR";

		g.add("IDENTIFIER_") << "ID_CHAR";
		g.add("IDENTIFIER_") << "IDENTIFIER_" << "ID_CHAR";
		g.add("IDENTIFIER", &parse_context::make_identifier) << "IDENTIFIER_";

		g.add("rule", &parse_context::make_rule) << "IDENTIFIER" << "WSP" << ':' << "WSP" << "rule_body" << ';';

		g.add("rule_body", &parse_context::make_rule_body) << "rule_item_list";
		g.add("rule_body", &parse_context::join_rule_body) << "rule_body" << '|' << "WSP" << "rule_item_list";

		g.add("rule_item_list", &parse_context::make_rule_item_list) << "rule_item";
		g.add("rule_item_list", &parse_context::make_rule_item_list) << "rule_item" << "WSP_CHAR" << "WSP";
		g.add("rule_item_list", &parse_context::join_rule_item_list) << "rule_item" << "WSP_CHAR" << "WSP" << "rule_item_list";
		
		g.add("rule_item") << "IDENTIFIER";
		g.add("rule_item") << "LITERAL";

		g.add("rules") << "WSP";
		g.add("rules") << "rules" << "rule" << "WSP";

		generate_lr1_tables_print_trace(g.begin(), g.end(), "rules", m_table, std::cout);
	}

	void extract(std::string const & str, grammar<rule<char, std::string> > & g)
	{
		parse_context ctx(g);

		char const * ptr = str.c_str();
		::parse(m_table, ptr, ptr + str.size(), parse_visitor(ctx));
	}

private:
	struct parse_context
	{
		typedef rule<char, std::string> rule_type;
		typedef rule_type::symbol_type symbol_type;
		typedef boost::variant<char, std::string> rule_item_type;
		
		std::stack<symbol_type> rule_items;
		std::stack<std::vector<symbol_type> > rule_item_lists;
		std::stack<std::vector<std::vector<symbol_type> > > rule_bodies;

		grammar<rule_type> & rules;

		explicit parse_context(grammar<rule_type> & g)
			: rules(g)
		{
		}

		void make_identifier(char const * first, char const * last)
		{
			rule_items.push(std::string(first, last));
		}

		void make_literal(char const * first, char const * last)
		{
			rule_items.push(first[1]);
		}

		void make_rule_item_list(char const * first, char const * last)
		{
			rule_item_lists.push(std::vector<rule_item_type>());
			rule_item_lists.top().push_back(rule_items.top());
			rule_items.pop();
		}

		void join_rule_item_list(char const * first, char const * last)
		{
			rule_item_lists.top().push_back(rule_items.top());
			rule_items.pop();
		}

		void make_rule_body(char const * first, char const * last)
		{
			rule_bodies.push(std::vector<std::vector<rule_item_type> >());
			rule_bodies.top().push_back(rule_item_lists.top());
			rule_item_lists.pop();
		}

		void join_rule_body(char const * first, char const * last)
		{
			rule_bodies.top().push_back(rule_item_lists.top());
			rule_item_lists.pop();
		}

		void make_rule(char const * first, char const * last)
		{
			std::string base = boost::get<std::string>(rule_items.top());
			std::vector<std::vector<symbol_type> > const & rule_body = rule_bodies.top();

			for (std::size_t i = 0; i < rule_body.size(); ++i)
			{
				rule_type & rule = rules.add(base);
				for (std::size_t j = rule_body[i].size(); j > 0; --j)
				{
					if (rule_body[i][j-1].which() == 0)
						rule << boost::get<char>(rule_body[i][j-1]);
					else
						rule << boost::get<std::string>(rule_body[i][j-1]);
				}
			}

			rule_items.pop();
			rule_bodies.pop();
		}
	};

	typedef void (parse_context::*action_type)(char const *, char const *);
	typedef rule<terminal_set<char>, std::string, action_type> rule_type;

	struct parse_visitor
	{
		parse_visitor(parse_context & ctx)
			: m_context(ctx)
		{
		}

		void reduce(action_type const & action, char const * first, char const * last)
		{
			if (action)
				(m_context.*action)(first, last);
		}

		parse_context & m_context;
	};

	lr1_table<terminal_set<char>, std::string, action_type> m_table;
};

#endif

// Generated by Bisonc++ V2.09.03 on Thu, 20 Feb 2014 23:14:29 +0100

#ifndef Parser_h_included
#define Parser_h_included

// $insert baseclass
#include "Parserbase.h"
// $insert scanner.h
#include "../scanner/Scanner.h"

#include <stack>
#include "../skusobna_trieda.h"
#include "../data_model/Model.h"
#include "../data_model/Entite.h"
//#include "../data_model/Normalizer.h"

#undef Parser
class Parser: public ParserBase
{
    // $insert scannerobject
        Scanner d_scanner;

        typedef double valueT;
        int line_num = 1;
        bool testing = true;
        bool verbatim = false;
        bool run = true;

        Model<valueT> storage;
        valueT paramFirstValue;
        std::stack<Entite<valueT> > eq;

    public:
        int parse();

        Parser() {}
        Parser(std::istream &in = std::cin, std::ostream &out = std::cout);

        Model<valueT>& returnStorage();

    private:
        void error(char const *msg);    // called on (syntax) errors
        int lex();                      // returns the next token from the
                                        // lexical scanner.
        void print();                   // use, e.g., d_token, d_loc

    // support functions for parse():
        void executeAction(int ruleNr);
        void errorRecovery();
        int lookup(bool recovery);
        void nextToken();
};


inline void Parser::error(char const *msg)
{
    std::cerr << msg << " at line "<< line_num << " before char "<< d_scanner.column_num << '\n';
}

// $insert lex
inline int Parser::lex()
{
    return d_scanner.lex();
}

// $insert print
inline void Parser::print()
{}

#endif

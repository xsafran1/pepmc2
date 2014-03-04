#include <cstdlib>
#include <iostream>
#include <fstream>
#include "parser/Parser.h"
#include "./data_model/Normalizer.h"
#include "./data_model/Normalizer.cpp"
#include "./data_model/Model.h"
#include "./data_model/Model.cpp"

using namespace std;

int main (int argc, char **argv)
{
    Parser parser(cin);
    parser.parse();
    Model &model = parser.returnStorage();

    Normalizer normalizer;
/*
    cout << "VARS: \n";
    for(int i = 0; i < model.getVariables().size(); i++) {
        cout << "\t" << model.getVariable(i) << endl;
    }
*/
	return 0;
}

#include <cstdlib>
#include <iostream>
#include <fstream>
#include "parser/Parser.h"
//#include "./data_model/Normalizer.h"
//#include "./data_model/Normalizer.cpp"
#include "./data_model/Model.h"
#include "./data_model/Model.cpp"

using namespace std;

int main (int argc, char **argv)
{
    Parser parser(cin);
    parser.parse();

    Model<double> &model = parser.returnStorage();

    model.RunAbstraction();

    ofstream out("final_equation.dat");

    for(int i = 0; i < model.getSigmoids().size(); i++) {
        out << model.getSigmoids().at(i) << endl;
    }

    out << endl;
    for(int i = 0; i < model.getEquations().size(); i++) {
        out << model.getVariable(model.getEquations().at(i).first) << " = " << model.getEquations().at(i).second.at(0) << endl;
        for(int j = 1; j < model.getEquations().at(i).second.size(); j++) {
            out << " + " << model.getEquations().at(i).second.at(j) << endl;
        }
        out << endl;
    }

    out << endl;
    for(int i = 0; i < model.getThresholds().size(); i++) {
        out << "THRES: " << model.getVariable(model.getThresholds().at(i).first) << ": " << model.getThresholds().at(i).second.at(0);
        for (int t = 1; t < model.getThresholds().at(i).second.size(); t++) {
            out << ", " << model.getThresholds().at(i).second.at(t);
        }
        out << endl;
    }

    if(!model.getInitsNames().empty()) {
        out << endl;
        out << "INIT: " << model.getInitsNames().at(0) << "," << model.getInitsValues().at(0).first << "," << model.getInitsValues().at(0).second;
        for(int i = 1; i < model.getInitsNames().size(); i++) {
            out << "; " << model.getInitsNames().at(i) << "," << model.getInitsValues().at(i).first << "," << model.getInitsValues().at(i).second;
        }
        out << endl;
    }


    if(!model.getVarPointsNames().empty()) {
        out << endl;
        out << "VAR_POINTS: " << model.getVarPointsNames().at(0) << ":" << model.getVarPointsValues().at(0).first << "," << model.getVarPointsValues().at(0).second;
        for(int i = 1; i < model.getVarPointsNames().size(); i++) {
            out << "; " << model.getVarPointsNames().at(i) << ":" << model.getVarPointsValues().at(i).first << "," << model.getVarPointsValues().at(i).second;
        }
        out << endl;
    }

	return 0;
}

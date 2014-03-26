#include <cstdlib>
#include <iostream>
#include <iomanip> 
#include <fstream>
#include "parser/Parser.h"
//#include "./data_model/Normalizer.h"
//#include "./data_model/Normalizer.cpp"
#include "./data_model/Model.h"
#include "./data_model/Model.cpp"

typedef unsigned int uint;

using namespace std;

int main (int argc, char **argv)
{
    Parser parser(cin);
    parser.parse();

    Model<double> &model = parser.returnStorage();

    model.RunAbstraction();

    ofstream out("final_equation.dat");

    for(uint i = 0; i < model.getSigmoids().size(); i++) {
        out << model.getSigmoids().at(i) << endl;
    }

    out << endl;

	out << fixed;
	out << setprecision(15);

    for(uint i = 0; i < model.getEquations().size(); i++) {
		std::pair<std::size_t, typename std::vector<Summember<double> > > eq = model.getEquations().at(i);
		std::vector<Summember<double> > eqi = eq.second;

        out << model.getVariable(eq.first) << " = " << endl;
        for(int j = 0; j < eqi.size(); j++) {

			Summember<double> sum = eqi.at(j);

			out << sum.GetConstant();

			if (sum.hasParam()) {
				
				out << "*" << model.getParamName(sum.GetParam());
			}
			for (uint i = 0; i < sum.GetVars().size(); i++) {
				out << "*" << model.getVariable(sum.GetVars().at(i)-1);
			}

			
			for (uint i = 0; i < sum.GetRamps().size(); i++) {
				


				if (sum.GetRamps().at(i).negative)
					out << "*rm(" << model.getVariable(sum.GetRamps().at(i).dim) << "," << sum.GetRamps().at(i).min << "," << sum.GetRamps().at(i).min_value << "," << sum.GetRamps().at(i).max << "," << sum.GetRamps().at(i).max_value << ")";
				else
					out << "*rp(" << model.getVariable(sum.GetRamps().at(i).dim) << "," << sum.GetRamps().at(i).min << "," << sum.GetRamps().at(i).min_value << "," << sum.GetRamps().at(i).max << "," << sum.GetRamps().at(i).max_value << ")";
				//return out;


				//out << "*" << sum.GetRamps().at(i);
			}

			for (uint i = 0; i < sum.GetSigmoids().size(); i++) {
				out << "*" << sum.GetSigmoids().at(i);
			}

			if (j != eqi.size()-1)
			{
				out << " + " << endl;
			}
        }
        out << endl;
    }

	
	out << endl;
	for (int i = 0; i < model.getEquations().size(); i++) {
		out << model.getVariable(model.getEquations().at(i).first) << " = " << model.getEquations().at(i).second.at(0) << endl;
		for (int j = 1; j < model.getEquations().at(i).second.size(); j++) {
			out << " + " << model.getEquations().at(i).second.at(j) << endl;
		}
		out << endl;
	}
	


    out << endl;
    for(uint i = 0; i < model.getThresholds().size(); i++) {
        out << "THRES: " << model.getVariable(model.getThresholds().at(i).first) << ": " << model.getThresholds().at(i).second.at(0);
        for (int t = 1; t < model.getThresholds().at(i).second.size(); t++) {
            out << ", " << model.getThresholds().at(i).second.at(t);
        }
        out << endl;
    }

    if(!model.getInitsNames().empty()) {
        out << endl;
        out << "INIT: " << model.getInitsNames().at(0) << "," << model.getInitsValues().at(0).first << "," << model.getInitsValues().at(0).second;
        for(uint i = 1; i < model.getInitsNames().size(); i++) {
            out << "; " << model.getInitsNames().at(i) << "," << model.getInitsValues().at(i).first << "," << model.getInitsValues().at(i).second;
        }
        out << endl;
    }


    if(!model.getVarPointsNames().empty()) {
        out << endl;
        out << "VAR_POINTS: " << model.getVarPointsNames().at(0) << ":" << model.getVarPointsValues().at(0).first << "," << model.getVarPointsValues().at(0).second;
        for(uint i = 1; i < model.getVarPointsNames().size(); i++) {
            out << "; " << model.getVarPointsNames().at(i) << ":" << model.getVarPointsValues().at(i).first << "," << model.getVarPointsValues().at(i).second;
        }
        out << endl;
    }

	return 0;
}

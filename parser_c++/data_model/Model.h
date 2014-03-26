#pragma once
#include <stdlib.h>
#include <string>
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include <cmath>
#include <time.h>

#include "Summember.h"
#include "Equation.h"
//#include "Entite.h"



using std::string;

template <typename T>
class Model
{
	typedef T value_type;

private:
/*
	struct ramp
	{
		std::size_t dim;
		value_type min;
		value_type max;
		value_type min_value;
		value_type max_value;
		bool negative;

		ramp(std::size_t dim, value_type min, value_type max, value_type minValue, value_type maxValue, bool negative = false)
                    : dim(dim), min(min), max(max), min_value(minValue), max_value(maxValue), negative(negative) {}

		value_type value(value_type value) const
		{
			value_type res = (value - min) / (max - min);
			res = min_value + (res * (max_value - min_value));
			if (res < 0)
				res = 0;
			else if (res > 1)
				res = 1;
			return negative ? 1 - res : res;
		}

		friend std::ostream& operator<<(std::ostream& out, const ramp& r) {
			if (r.negative)
				out << "R(-)(" << r.dim << "," << r.min << "," << r.max << "," << r.min_value << "," << r.max_value << ")";
			else
				out << "R(+)(" << r.dim << "," << r.min << "," << r.max << "," << r.min_value << "," << r.max_value << ")";
			return out;
		}
	};
*/
	struct sigmoid
	{
		std::size_t dim;
		value_type k;
		value_type theta;
		value_type a;
		value_type b;
		std::size_t n;
		bool positive;
		bool isInverse;

		friend std::ostream& operator<<(std::ostream& out, const sigmoid& s) {
			if (!s.positive)
				out << "S(-)[" << s.n << "](" << s.dim << "," << s.k << "," << s.theta << "," << s.a << "," << s.b << ")";
			else
				out << "S(+)[" << s.n << "](" << s.dim << "," << s.k << "," << s.theta << "," << s.a << "," << s.b << ")";
			return out;
		}

		std::vector<value_type> enumerateYPoints(std::vector<value_type> x)
		{
			std::vector<value_type> y;
			value_type tempA = a;
			value_type tempB = b;

			if (isInverse) {
				if (!positive) {
					tempA = b;
					tempB = a;
				}

				for (int i = 0; i < x.size(); i++) {
					//y.push_back((1 / tempA) + ((1 / tempB) - (1 / tempA))*((1 + tanh(k*(x.at(i) - (theta + log(tempB / tempA) / (2 * k)))))*0.5));
					y.push_back(1 / (tempA + (tempB - tempA)*((1 + tanh(k*(x.at(i) - theta)))*0.5)));
				}

			}
			else {
				if (!positive) {
					tempA = b;
					tempB = a;
				}

				for (int i = 0; i < x.size(); i++) {
					y.push_back(tempA + (tempB - tempA)*((1 + tanh(k*(x.at(i) - theta)))*0.5));
				}
			}
			return y;
		}

	};

	std::vector<sigmoid> sigmoids;

public:
	void AddVariable(string var);
	void AddParam(string param);
	void AddParamRange(value_type a, value_type b);
	void AddConstantName(string constant);
	void AddConstantValue(value_type constant);

	void AddSigmoid(std::size_t segments, std::size_t dim, value_type k, value_type theta,
		value_type a, value_type b, bool positive = 1, bool isInverse = 0);

	void AddSigmoid(sigmoid & new_sigmoid);

	void AddEquation(std::vector<Summember<T> > summs);
	void AddEquationName(std::string var);

	void AddThresholdName(std::string var);
	void AddThresholdValue(std::string value);

	void AddVarPointsName(std::string var);
	void AddVarPointsFstValue(std::string value);
	void AddVarPointsSndValue(std::string value);

	void AddInitsName(std::string var);
	void AddInitsFstValue(std::string value);
	void AddInitsSndValue(std::string value);

	void AddBaLine(std::string);

	std::size_t GetSigmoidsSize();

    const std::vector<std::string> getVariables() const;
	const std::string getVariable(int index) const;

    const std::vector<std::string> getParamNames() const;
	const std::string getParamName(int index) const;
    const std::vector<std::pair<value_type, value_type> > getParamRanges() const;
	const std::pair<value_type, value_type> getParamRange(int index) const;

	const std::vector<std::pair<std::string, value_type> > getConstants() const;
	const std::pair<std::string, value_type> getConstant(int index) const;

	const std::vector<std::pair<std::size_t, std::vector<Summember<T> > > > getEquations() const;

	const std::vector<std::pair<std::size_t, std::vector<value_type> > > getThresholds() const;

	const std::vector<std::pair<value_type, value_type> > getVarPointsValues() const;
	const std::vector<std::string> getVarPointsNames() const;

	const std::vector<std::pair<std::size_t, std::size_t> > getInitsValues() const;
	const std::vector<std::string> getInitsNames() const;

	const std::vector<std::string> getBaLines() const;

	const std::vector<sigmoid> getSigmoids() const;

	void RunAbstraction();

private:
	std::vector<std::size_t> FindSigmoids(std::size_t dim);

	std::vector<std::string> var_names;  //variables
	std::vector<std::string> param_names;  //params
	std::vector<std::pair<value_type, value_type> > param_ranges;  //params
	std::vector<std::pair<std::string, value_type> > constants;  //constants
	//std::vector<std::pair<std::size_t, Entite<T> > > equations;
	std::vector<std::pair<std::size_t, std::vector<Summember<T> > > > equations;
	std::vector<std::pair<std::size_t, std::vector<value_type> > > thresholds;
	std::vector<std::size_t> var_points;
	std::vector<std::pair<value_type, value_type> > var_points_values;
	std::vector<std::size_t> inits;
	std::vector<std::pair<std::size_t, std::size_t> > inits_values;
	std::vector<std::string> ba_lines;


    std::vector<double> computeThresholds(std::vector<std::size_t> s, int numOfSegments, int numOfX = 0);
    std::vector<std::vector<double> > generateSpace(std::vector<std::size_t> s, std::vector<double> &x, int numOfX);
    std::vector<double> generateXPoints (double ai, double bi, int num_segments);
    std::vector<double> segmentErr (std::vector <double> x, std::vector <double> y);
    std::vector<double> optimalGlobalLinearApproximation(std::vector<double> x, std::vector<std::vector<double> > y, int n_segments);
    std::vector<std::vector<typename Summember<value_type>::ramp> > generateNewRamps(std::vector<double> x, std::vector< std::vector<double> > y, std::size_t dim);
};

template <typename T>
void Model<T>::AddBaLine(std::string ba) {
    ba_lines.push_back(ba);
}

template <typename T>
void Model<T>::AddInitsName(std::string var) {
    int indexOfVar = -1;
    for (int i = 0; i < var_names.size(); i++) {
        if (var_names.at(i).compare(var) == 0 ) {
            indexOfVar = i;
            break;
        }
    }
    if(indexOfVar >= 0 && indexOfVar < var_names.size())
        inits.push_back(indexOfVar);
}

template <typename T>
void Model<T>::AddInitsFstValue(std::string value) {
    std::pair<std::size_t, std::size_t> values;
    values.first = std::stoi(value);
    inits_values.push_back(values);
}

template <typename T>
void Model<T>::AddInitsSndValue(std::string value) {
    inits_values.back().second = std::stoi(value);
}

template <typename T>
void Model<T>::AddVarPointsName(std::string var) {
    int indexOfVar = -1;
    for (int i = 0; i < var_names.size(); i++) {
        if (var_names.at(i).compare(var) == 0 ) {
            indexOfVar = i;
            break;
        }
    }
    if(indexOfVar >= 0 && indexOfVar < var_names.size())
        var_points.push_back(indexOfVar);
}

template <typename T>
void Model<T>::AddVarPointsFstValue(std::string value) {
    std::pair<T, T> values;
    values.first = (T)std::stod(value);
    var_points_values.push_back(values);
}

template <typename T>
void Model<T>::AddVarPointsSndValue(std::string value) {
    var_points_values.back().second = (T)std::stod(value);
}

template <typename T>
void Model<T>::AddThresholdName(std::string var) {

    int indexOfVar = -1;
    for (int i = 0; i < var_names.size(); i++) {
        if (var_names.at(i).compare(var) == 0 ) {
            indexOfVar = i;
            break;
        }
    }

    int i = 0;
    for( ; i < thresholds.size(); i++) {
        if(thresholds.at(i).first == indexOfVar) {
            if(i < thresholds.size() - 1) {
                swap(thresholds.at(i), thresholds.at(thresholds.size() - 1));
            }
            i = 0;
            break;
        }
    }
    if(i == thresholds.size()) {
        std::pair<std::size_t, std::vector<T> > p;
        std::vector<T> th;
        p.first = indexOfVar;
        p.second = th;
        thresholds.push_back(p);
    }
}

template <typename T>
void Model<T>::AddThresholdValue(std::string value) {
    if(!thresholds.empty())
        thresholds.at(thresholds.size() - 1).second.push_back((T)std::stod(value));
}

template <typename T>
void Model<T>::AddEquationName(std::string var) {
    std::pair<std::size_t, std::vector<Summember<T> > > eq;

    for (int i = 0; i != var_names.size(); i++) {
        if (var_names.at(i).compare(var) == 0 ) {
            std::cout << "I have found var for eq:" << var_names.at(i) << ";\n";
            eq.first = i;
        }
    }
    //TODO: chcelo by to kontrolu ci sa nejaka premenna vobec nasla

    equations.push_back(eq);
}

template <typename T>
void Model<T>::AddEquation(std::vector<Summember<T> > summs) {
    if(!equations.empty()) {
        std::cout << "I'm saving summs\n";
        equations.back().second = summs;
    }
}


template <typename T>
void Model<T>::AddVariable(string var)
{
	var_names.push_back(var);
}

template <typename T>
void Model<T>::AddParam(string param)
{
	param_names.push_back(param);
}

template <typename T>
void Model<T>::AddParamRange(value_type a, value_type b)
{
	std::pair<value_type, value_type> p;
	p.first = a;
	p.second = b;

	param_ranges.push_back(p);
}

template <typename T>
void Model<T>::AddConstantName(string constant)
{
	std::pair<std::string, value_type> p;
	p.first = constant;
	constants.push_back(p);
}

template <typename T>
void Model<T>::AddConstantValue(value_type constant)
{
	if (constants.empty())
	{
		//ERROR /*TODO*/
	}

	std::pair<std::string, value_type> & p = constants.back();
	p.second = constant;
}

template <typename T>
void Model<T>::AddSigmoid(std::size_t segments, std::size_t dim, value_type k, value_type theta,
	value_type a, value_type b, bool positive, bool isInverse)
{
	sigmoid s;
	s.n = segments;
	s.dim = dim;
	s.k = k;
	s.theta = theta;
	s.a = a;
	s.b = b;
	s.positive = positive;
	s.isInverse = isInverse;
	sigmoids.push_back(s);
}

template <typename T>
void Model<T>::AddSigmoid(sigmoid & new_sigmoid)
{
	sigmoids.push_back(new_sigmoid);
}

template <typename T>
std::size_t Model<T>::GetSigmoidsSize()
{
	return sigmoids.size();
}


template <typename T>
const std::vector<std::string> Model<T>::getVariables() const {
	return var_names;
}

template <typename T>
const std::string Model<T>::getVariable(int index) const {
	return var_names.at(index);
}

template <typename T>
const std::vector<std::string> Model<T>::getParamNames() const {
    return param_names;
}

template <typename T>
const std::string Model<T>::getParamName(int index) const {
    return param_names.at(index);
}

template <typename T>
const std::vector<std::pair<T, T> > Model<T>::getParamRanges() const {
    return param_ranges;
}

template <typename T>
const std::pair<T, T> Model<T>::getParamRange(int index) const {
    return param_ranges.at(index);
}

template <typename T>
const std::vector<std::pair<std::string, T> > Model<T>::getConstants() const {
    return constants;
}

template <typename T>
const std::pair<std::string, T> Model<T>::getConstant(int index) const {
    return constants.at(index);
}

template <typename T>
const std::vector<std::pair<std::size_t, typename std::vector<Summember<T> > > > Model<T>::getEquations() const {
    return equations;
}

template <typename T>
const std::vector<std::pair<std::size_t, std::vector<T> > > Model<T>::getThresholds() const {
    return thresholds;
}

template <typename T>
const std::vector<std::pair<T, T> > Model<T>::getVarPointsValues() const {
    return var_points_values;
}

template <typename T>
const std::vector<std::string> Model<T>::getVarPointsNames() const {
    std::vector<std::string> vpn;
    for(int i = 0; i < var_points.size(); i++) {
        vpn.push_back(var_names.at(var_points.at(i)));
    }
    return vpn;
}

template <typename T>
const std::vector<std::pair<std::size_t, std::size_t> > Model<T>::getInitsValues() const {
    return inits_values;
}

template <typename T>
const std::vector<std::string> Model<T>::getInitsNames() const {
    std::vector<std::string> vpn;
    for(int i = 0; i < inits.size(); i++) {
        vpn.push_back(var_names.at(inits.at(i)));
    }
    return vpn;
}

template <typename T>
const std::vector<std::string> Model<T>::getBaLines() const {
    return ba_lines;
}

template <typename T>
const std::vector<typename Model<T>::sigmoid> Model<T>::getSigmoids() const {
    return sigmoids;
}


template <typename T>
std::vector<std::size_t> Model<T>::FindSigmoids(std::size_t dim)
{
	std::vector<std::size_t> result;

	for (uint i = 0; i < sigmoids.size(); i++)
	{
		if (sigmoids.at(i).dim == dim + 1)
		{
			result.push_back(i);
		}

	}

	return result;
}

template <typename T>
void Model<T>::RunAbstraction()
{
    // dostane alebo si zoberie priamo ako class method vector so vsetkymi sigmoidami a rozdeli ich podla Vars do skupin
    // postupne vsetky skupiny sigmoidov posle funkcii comuteThresholds, ktore zaroven ulozi medzi ostatne thresholdy
    // nasledne podla tychto novych thresholdov vytvori rampy pre vsetky sigmoidy zo skupiny a ulozi medzi rampy
    // nakoniec mozno zmaze sigmoidy ak uz nebudu treba

	std::vector<std::vector<typename Summember<T>::ramp> > new_ramps;
	unsigned int sigmoidNum = 0;

    for(int i = 0; i < var_names.size(); i++) {

        std::vector<std::size_t> groupOfSigmoids = FindSigmoids(i);
        std::cout << "For var of index " << i << " has been found " << groupOfSigmoids.size() << " sigmoids\n";

        if(groupOfSigmoids.empty())
            continue;       // no sigmoids for that variable

        int numOfSegments = 5;     //TODO: treba dorobit s ohladom na VAR_POINTS: a hodnoty v hranatych zatvorkach u sigmoidov
        int numOfXPoints = 0;       //TODO: treba dorobit s ohladom na VAR_POINTS: pre danu premennu

        for(int j = 0; j < var_points.size(); j++) {
            if(i == var_points.at(j)) {
                if(numOfSegments < var_points_values.at(j).second)
                    numOfSegments = var_points_values.at(j).second;

                if(numOfXPoints < var_points_values.at(j).first)
                    numOfXPoints = var_points_values.at(j).first;
            }
        }

        std::vector<double> thresholdsX = computeThresholds(groupOfSigmoids,numOfSegments,numOfXPoints);

    //TODO: ODSKUSAT: tu sa ukladaju nove thresholdy k ostatnym
        AddThresholdName(getVariable(i));
        for(int t = 0; t < thresholdsX.size(); t++) {
            std::stringstream ss;
            ss << thresholdsX.at(t);
            AddThresholdValue(ss.str());
        }

        std::vector<std::vector<double> > thresholdsY;

        for(int j = 0; j < groupOfSigmoids.size(); j++) {

            thresholdsY.push_back(sigmoids.at(groupOfSigmoids.at(j)).enumerateYPoints(thresholdsX));

            // Testing functionality
            std::stringstream ss;
            ss << sigmoidNum++;
            std::string fileName = "test_curve" + ss.str() + ".dat";
            std::ofstream out(fileName,std::ofstream::out | std::ofstream::trunc);
            if(out.is_open()) {
                for(int sp = 0; sp < thresholdsX.size(); sp++) {
                    out << thresholdsX.at(sp) << "\t" << thresholdsY.back().at(sp) << "\n";
                }
            }
            out.close();
            // End of testing
        }

        new_ramps = generateNewRamps(thresholdsX, thresholdsY, i);

        // For testing
        std::cout << "----------new ramps----------\n";
        for(int vr = 0; vr < new_ramps.size(); vr++) {
            std::cout << "----new sigmoid----\n";
            for(int r = 0; r < new_ramps.at(vr).size(); r++) {
                std::cout << new_ramps.at(vr).at(r) << std::endl;
            }
        }
        std::cout << "------end of new ramps-------\n";

        // for all equations
        for(int j = 0; j < equations.size(); j++) {
            std::cout << "in EQ " << j << "\n";
            int summsCounter = 0;
            // for all summembers in one equation
            for(typename std::vector<Summember<T> >::iterator sit = equations.at(j).second.begin(); sit != equations.at(j).second.end(); sit++) {
            //for(int s = 0; s < equations.at(j).second.size(); s++) {
                std::cout << "in Summember:" << summsCounter++ << "\n";
                Summember<T> summ = *sit;
                //Summember<T> summ = equations.at(j).second.at(s);

                // for all sigmoids in one summember
                for(int g = 0; g < summ.GetSigmoids().size(); g++) {
                    std::cout << "in sigmoid " << g << "\n";
                    std::size_t index = (summ.GetSigmoids().at(g)) - 1;

                    // for all sigmoids found for one variable
                    for(int v = 0; v < groupOfSigmoids.size(); v++) {
                        if(index == groupOfSigmoids.at(v)) {
                            std::cout << "TERAZ TREBA NAHRADIT SIGMOID " << v << " RAMPAMI\n";
                            std::vector<Summember<T> > newSummembers = summ.sigmoidAbstraction(new_ramps.at(v), index+1);
                            std::cout << "pocet new summs:" << newSummembers.size() << "\n";

                            std::cout << "pocty summs:" << equations.at(j).second.size() << ",";
                            typename std::vector<Summember<T> >::iterator newSit;
                            newSit = equations.at(j).second.erase(sit);
                            std::cout << equations.at(j).second.size() << ",";

                            typename std::vector<Summember<T> >::iterator replacingSit;
                            for(replacingSit = newSummembers.begin(); replacingSit != newSummembers.end(); replacingSit++) {
                                sit = equations.at(j).second.insert(newSit, *replacingSit);
                                newSit = sit;
                            }
                            //sit = equations.at(j).second.insert(newSit, newSummembers.begin(), newSummembers.end());
                            std::cout << equations.at(j).second.size() << "\n";
                            summ = *sit;
                            g = -1;
                            summsCounter = 0;
                            std::cout << "USPESNE NAHRADENE\n";

                            break;
                      // TODO: ak sa rovnaju treba rampami v new_ramps.at(v) nahradit najdeny vyskyt sigmoidu sigmoids.at(index)
                            // v j-tej rovnici a v s-tom summembre tak ze sa tento summember odstrani a miesto neho vzniknu uplne
                            // nove summembre (jeden pre kazdu rampu z new_ramps.at(v)) so vsetkymi ostatnymi clenmi zachovanymi
                            // Po najdeni by teoreticky mohol nasledovat masivny break az k prvemu for cyklu ale neviem isto,
                            // ci kazdy sigmoid musi byt unikatny
                            // TREBA DAVAT POZOR PRI VKLADANI NOVYCH SUMMEMBROV - najlepsie bude ulozit do docasnej struktury
                            // a po spravnom cykle ich ulozit
                        }
                    }
                }
            }
        }


    }
	/*
	sigmoids zde v modelu obsahuje vsechny sigmoidy ze vsech rovnic

	v summemberu jsou ve vektoru sigmoids hodnoty int, odkazujici na poradi sigmoidu ve vektoru v modelu

	vysledkem abstrakce by mel bej vektor vektoru ramp, kterej se na zaver ulozi do ramp v summemberech
	- pozice vnejsiho vektoru ramp odpovida pozici sigmoide (a proto odkaz ze summemberu bude odkazovat i na vektor ramp]

	bylo by vhodny summembery ukladat ve vektoru do vektoru novych trid Equation, uz nebude potreba pretizenych operatoru a ostatnich metod


	*/
}

template <typename T>
std::vector<std::vector<typename Summember<T>::ramp> > Model<T>::generateNewRamps(std::vector<double> x, std::vector< std::vector<double> > y, std::size_t dim) {
    std::vector<std::vector<typename Summember<T>::ramp> > result;

    for(int i = 0; i < y.size(); i++) {

        std::vector<typename Summember<T>::ramp> ramps;

        for(int t = 0; t < x.size() - 1; t++) {
            double x1 = x.at(t);
            double x2 = x.at(t+1);
            double y1 = y.at(i).at(t);
            double y2 = y.at(i).at(t+1);

            if(y1 <= y2)
                ramps.push_back(typename Summember<T>::ramp::ramp(dim, x1, x2, y1, y2));
            else
                ramps.push_back(typename Summember<T>::ramp::ramp(dim, x1, x2, y1, y2, true));
        }

        result.push_back(ramps);
    }

    return result;
}

template <typename T>
std::vector<double> Model<T>::computeThresholds(std::vector<std::size_t> s, int numOfSegments, int numOfX) {

    //TODO: treba sa dohodnut ohladom obsahu hranatych zatvoriek u jednotlivych sigmoidov
    for(int i = 0; i < s.size(); i++) {
        if(numOfSegments < sigmoids.at(s.at(i)).n) {
            numOfSegments = sigmoids.at(s.at(i)).n;
        }
    }

    std::cout << "NUMBER OF SEGMENTS = " << numOfSegments << std::endl;

    std::vector<double> xPoints;
    std::vector<std::vector<double> > curves = generateSpace(s,xPoints,numOfX);
    std::vector<double> segmentsPoints;

    std::cout << "xPoints.size() = " << xPoints.size() << std::endl;
    std::cout << "curves.size() = " << curves.size() << std::endl;

    clock_t start, finish;          //TODO: neskor zmazat
    double durationInSec;           //TODO: neskor zmazat
/*
    start = clock();                //TODO: neskor zmazat
    segmentsPoints = optimalFastGlobalLinearApproximation2 (xPoints, curves, numOfSegments);

    finish = clock();               //TODO: neskor zmazat
    durationInSec = (double)(finish - start) / CLOCKS_PER_SEC;          //TODO: neskor zmazat
    std::cout << "duration = " << durationInSec << " sec. Found = ";          //TODO: neskor zmazat
    for(int i = 0; i < segmentsPoints.size(); i++)
        std::cout << segmentsPoints.at(i) << ",";
    std::cout << std::endl;
*/

    start = clock();                //TODO: neskor zmazat

    std::cout << "before optimalGlobalLinear...\n";
    segmentsPoints = optimalGlobalLinearApproximation (xPoints, curves, numOfSegments);
    std::cout << "after optimalGlobalLinear...\n";

    finish = clock();               //TODO: neskor zmazat
    durationInSec = (double)(finish - start) / CLOCKS_PER_SEC;      //TODO: neskor zmazat
    std::cout << "duration = " << durationInSec << " sec. Found = ";     //TODO: neskor zmazat
    for(int i = 0; i < segmentsPoints.size(); i++)                  //TODO: neskor zmazat
        std::cout << segmentsPoints.at(i) << ",";                        //TODO: neskor zmazat
    std::cout << std::endl;                                                   //TODO: neskor zmazat

    return segmentsPoints;
}


template <typename T>
std::vector <double>  Model<T>::generateXPoints (double ai, double bi, int num_segments)
{
	   double a = ai;
	   double b = bi;

	   std::vector <double > x;

	   double dx = (b-a)/(num_segments-1);

	   for (int i = 0; i < num_segments; i++)
	   {
		   double cx = a + dx*i;
		   x.push_back(cx);
	   }

	   return x;
}


template <typename T>
std::vector<std::vector<double> > Model<T>::generateSpace(std::vector<std::size_t> s, std::vector<double> &x, int numOfX) {

    std::vector<std::vector<double> > y;

    if(s.size() > 0) {

        double intervalDeviationParam = 1.5;

        double min = sigmoids.at(s.at(0)).theta - (2.0 / sigmoids.at(s.at(0)).k) * intervalDeviationParam;       //TODO: bude treba .theta a .k nahradit spravnou funkciou
        double max = sigmoids.at(s.at(0)).theta + (2.0 / sigmoids.at(s.at(0)).k) * intervalDeviationParam;       //TODO: bude treba .theta a .k nahradit spravnou funkciou

        if(s.size() > 1) {

            for(int i = 1; i < s.size(); i++) {

                double tempMin = sigmoids.at(s.at(i)).theta - (2.0 / sigmoids.at(s.at(i)).k) * intervalDeviationParam;       //TODO: bude treba .theta a .k nahradit spravnou funkciou
                double tempMax = sigmoids.at(s.at(i)).theta + (2.0 / sigmoids.at(s.at(i)).k) * intervalDeviationParam;       //TODO: bude treba .theta a .k nahradit spravnou funkciou

                if(tempMin < min) {
                    min = tempMin;
                }
                if(tempMax > max) {
                    max = tempMax;
                }
            }
        }

        if(numOfX != 0) {
            x = generateXPoints(min, max, numOfX);
        } else {
            x = generateXPoints(min, max, (max - min)*100);
        }

        for(int i = 0; i < s.size(); i++) {
            y.push_back(sigmoids.at(s.at(i)).enumerateYPoints(x));
        }
    }

    return y;
}


template <typename T>
std::vector <double> Model<T>::segmentErr (std::vector <double> x, std::vector <double> y)
{
       // Find out size of x
       int nx = x.size();
       int ny = y.size();

       std::vector<double> result (3, 0.0);

       if (nx != ny)
       {
           std::cout << "Error in segmentErr: nx is not consistent with ny\n";
           return result;
       }

       // Compute line segment coefficients
       double a = (y[nx-1] - y[0]) / (x[nx-1] - x[0]);
       double b = (y[0] * x[nx-1] - y[nx-1] * x[0]) / (x[nx-1] - x[0]);

       // Compute error for above line segment
       double e = 0;

	   for (int k = 0; k < nx; k++)
	   {
		    e += pow((y[k] - a * x[k] - b),2);
	   }
	   e /= (pow(a,2) + 1);

       result[0] = e;
       result[1] = a;
       result[2] = b;

       return result;
}


template <typename T>
std::vector<double> Model<T>::optimalGlobalLinearApproximation(std::vector<double> x, std::vector<std::vector<double> > y,
                                                               int n_segments)
{
       int n_points = x.size();
       std::cout << "x.size() = " << n_points << std::endl;
       int n_curves = y.size();
       std::cout << "y.size() = " << n_curves << std::endl;

       std::vector<std::vector<double> > mCost (n_points, std::vector<double>(n_segments, INFINITY));
       std::vector<std::vector<double> > hCst  (n_points, std::vector<double>(n_points, INFINITY));

       mCost[1][0] = 0.0;

       std::vector<std::vector<int> > father (n_points, std::vector<int>(n_segments, 0));



       for (int n = 1; n < n_points; n++)
       {
            double temp = -1 * INFINITY;

            //std::cout << "temp =" << temp << "\n";

            for (int ic = 0; ic < n_curves; ic++)
            {
                 std::vector<double> v1 (x.begin(), x.begin() + n+1);
                 std::vector<double> v2 (y[ic].begin(), y[ic].begin() + n+1);
                 std::vector<double> seg_err = segmentErr(v1, v2);

                 temp = std::max(seg_err[0], temp);
            }

            mCost [n][0]  = temp;
            father[n][0]  = 0;
            //std::cout << " n=" << n << " mCost[" << n << "][0]=" << temp << " father[" << n << "][0]=" << father[n][0] << "\n";
       }

       double minErr, currErr;
       int    minIndex;

       for (int m = 1; m < n_segments; m++)
       {
            std::cout << "segment m=" << m << "\n";
            for (int n = 2; n < n_points; n++)
            {

                minErr   = mCost[n-1][m-1];
                minIndex = n - 1;

                for (int i = m; i <= n-2; i++)
                {
                    if (hCst[i][n]==INFINITY)
                    {
                        double temp = -1 * INFINITY;

                        for (int ic = 0; ic < n_curves; ic++)
                        {
                             std::vector<double> v1 (x.begin() + i, x.begin() + n+1);
                             std::vector<double> v2 (y[ic].begin() + i, y[ic].begin() + n+1);
                             std::vector<double> seg_err = segmentErr(v1, v2);

                             temp = std::max(seg_err[0], temp);
                        }

                        hCst[i][n] = temp;
                    }

                    currErr = mCost[i][m-1] + hCst[i][n];

                    if (currErr < minErr)
                    {
                        minErr   = currErr;
                        minIndex = i;
                    }
                }
               mCost[n][m]  = minErr;
               father[n][m] = minIndex;
         //  std::cout << " n=" << n << " mCost[" << n << "][" << m << "]=" << mCost[n][m] << " father[" << n << "][" << m << "]=" << father[n][m] << "\n";
        }
    }

    std::vector<int> ib (n_segments+1, 0);
    std::vector<double> xb (n_segments+1, 0.0);

    ib[n_segments] = n_points-1;
    xb[n_segments] = x[ib[n_segments]];
    //std::cout << "x[ib[n_segments]]=" << x[ib[n_segments]] << "\n";
    for (int i = n_segments-1; i >= 0; i--)
    {
         ib[i] = father[ib[i+1]][i];
         xb[i] = x[ib[i]];
         //std::cout << "x" << n_points - i << "=" << xb[i] << "\n";
    }

    for (int i = 0; i < n_segments + 1; i++)
    {
        std::cout << "x[" << i << "] =" << xb[i] << "\n";
    }

    return xb;
}


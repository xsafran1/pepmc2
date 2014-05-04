#pragma once

#include <string>
#include <stdexcept>
#include <cmath>
#include <sstream>
#include <fstream>
#include "Summember.h"
#include "Model.h"


typedef unsigned int uint;

template <typename T>
class Entite;

template <typename T>
class Entite
{
public:
	typedef T value_type;



    //Entite() {}
	Entite(Model<T> & model) : model(model) {}

	// Access methods
	void PutString(std::string str);
	void PutNumber(std::string number);

	void PutRp(std::string var, std::string theta1, std::string theta2, std::string a, std::string b);
	void PutRm(std::string var, std::string theta1, std::string theta2, std::string a, std::string b);
	void PutRpCoor(std::string var, std::string theta1, std::string theta2, std::string y1, std::string y2);
	void PutRmCoor(std::string var, std::string theta1, std::string theta2, std::string y1, std::string y2);


	void PutSp(std::string points, std::string var, std::string k, std::string theta1, std::string a, std::string b);
	void PutSm(std::string points, std::string var, std::string k, std::string theta1, std::string a, std::string b);
	void PutSpInv(std::string points, std::string var, std::string k, std::string theta1, std::string a, std::string b);
	void PutSmInv(std::string points, std::string var, std::string k, std::string theta1, std::string a, std::string b);

    void PutHp(std::string var, std::string theta, std::string a, std::string b, std::string accuracy);
    void PutHm(std::string var, std::string theta, std::string a, std::string b, std::string accuracy);
    
    void PutHillp(std::string var, std::string theta, std::string n, std::string a, std::string b);
    void PutHillm(std::string var, std::string theta, std::string n, std::string a, std::string b);

	///////

	std::vector<Summember<T> > & GetSummembers() //const
	{
		return summembers;
	}
/*
	Summember<T> * GetSigmoid() //const
	{
		return sigmoids.pop_back();
	}
*/
	void AddSummember(Summember<T> const & sm)
	{
		summembers.push_back(sm);
	}

	void clear()
	{
		summembers.clear();
	}

	bool empty() const
	{
		return summembers.empty();
	}

	std::size_t size() const
	{
		return summembers.size();
	}

	Summember<T> const & operator[](std::size_t i) const
	{
		return summembers.at(i);
	}

	void negate() {
	    for(uint i = 0 ; i < size(); i++) {
	        summembers.at(i).negate();
	    }
	}


	// Operators

	/*const*/ Entite<T> operator+(/*const*/ Entite<T> & e2);

	const Entite<T>  operator*(/*const*/ Entite<T> &);

	template <class U>
	friend std::ostream& operator<<(std::ostream& out, const Entite<U>& e);


private:

	void PutConst(std::size_t c);
	void PutParam(std::size_t p);
	void PutVar(std::size_t v);

	T getNumberFromString(std::string s);


    Model<T> & model;
	//std::vector<std::string> var_names;  //variables
	//std::vector<std::string> param_names;  //params
	//std::vector<std::string> constant_names;  //constants


	std::vector<Summember<T> > summembers;
};

template <typename T>
T Entite<T>::getNumberFromString(std::string s) {
    T result;
    try {
        result = (T)std::stod(s);
    } catch(std::invalid_argument& ) {
        for(uint i = 0; i < model.getConstants().size(); i++) {
	        if(s.compare(model.getConstant(i).first) == 0) {
	            result = model.getConstant(i).second;
	            break;
	        }
	    }
    }
    return result;
}


template <typename T>
void Entite<T>::PutString(std::string str)
{
	std::size_t i = 0;
	bool run = 1; // one string, one type

    for(; i < model.getVariables().size(); i++) {
        if(str.compare(model.getVariable(i)) == 0) {
            PutVar(i+1);
            run = 0;
            break;
        }
    }
    /*
    //-------NETUSIM PROC ALE TEN ITERATOR PROSTE HADZE SEGMENTATION FAULT----------------

	for (typename std::vector<std::string>::const_iterator it = model.getVariables().begin(); it != model.getVariables().end(); it++)
	{
		i++;
		int res = str.compare(0,std::string::npos,(*it));
		if (0 == res) {
			PutVar(i);
			run = 0;
			break;
		}
	} */

	if (1 == run) {

	    for(i = 0; i < model.getParamNames().size(); i++) {
	        if(str.compare(model.getParamName(i)) == 0) {
	            PutParam(i+1);
	            run = 0;
	            break;
	        }
	    }
	    /*
	    i = 0;
		for (typename std::vector<std::string>::const_iterator it = model.getParamNames().begin(); it != model.getParamNames().end(); it++)
		{
			i++;
			int res = str.compare((*it));
			if (0 == res) {
				PutParam(i);
				run = 0;
				break;
			}
		}*/
	}

	if (1 == run) {
	    for(i = 0; i < model.getConstants().size(); i++) {
	        if(str.compare(model.getConstant(i).first) == 0) {
	            PutConst(i);
	            run = 0;
	            break;
	        }
	    }
	    /*
	    i = 0;
		for (typename std::vector<std::pair<std::string, value_type> >::const_iterator it = model.getConstants().begin(); it != model.getConstants().end(); it++)
		{
			i++;
			int res = str.compare((*it).first);
			if (0 == res) {
				PutConst(i);
				break;
			}
		}*/
	}

}

template <typename T>
void Entite<T>::PutNumber(std::string number)
{
	double cc = std::stod(number);
	T c = (T)cc;

	Summember<T> new_summember;

	new_summember.AddConstant(c);
	AddSummember(new_summember);
}

template <typename T>
void Entite<T>::PutConst(std::size_t c)
{
    Summember<T> new_summember;
	new_summember.AddConstant(model.getConstant(c).second);
	AddSummember(new_summember);
}

template <typename T>
void Entite<T>::PutVar(std::size_t v)
{
    Summember<T> new_summember;
	new_summember.AddVar(v);
	AddSummember(new_summember);
}

template <typename T>
void Entite<T>::PutParam(std::size_t p)
{
    Summember<T> new_summember;
	new_summember.AddParam(p);
	AddSummember(new_summember);
}



template <typename T>
void Entite<T>::PutRp(std::string var, std::string theta1, std::string theta2, std::string a, std::string b)
{
    T y1 = getNumberFromString(theta1) * getNumberFromString(a) + getNumberFromString(b);
    T y2 = getNumberFromString(theta2) * getNumberFromString(a) + getNumberFromString(b);
    Summember<T> new_summember;
    for(uint i = 0; i < model.getVariables().size(); i++) {
        if(var.compare(model.getVariable(i)) == 0) {
            new_summember.AddRamp(i+1,getNumberFromString(theta1),getNumberFromString(theta2),y1,y2,false);
            AddSummember(new_summember);
            return;
        }
    }
    //TODO: i dont know what will happen if var wasn't find in variables

}

template <typename T>
void Entite<T>::PutRm(std::string var, std::string theta1, std::string theta2, std::string a, std::string b)
{
    T y1 = getNumberFromString(theta1) * getNumberFromString(a) + getNumberFromString(b);
    T y2 = getNumberFromString(theta2) * getNumberFromString(a) + getNumberFromString(b);
    Summember<T> new_summember;
    for(uint i = 0; i < model.getVariables().size(); i++) {
        if(var.compare(model.getVariable(i)) == 0) {
            new_summember.AddRamp(i+1,getNumberFromString(theta1),getNumberFromString(theta2),y1,y2,true);
            AddSummember(new_summember);
            return;
        }
    }
    //TODO: i dont know what will happen if var wasn't find in variables

}

template <typename T>
void Entite<T>::PutRpCoor(std::string var, std::string theta1, std::string theta2, std::string y1, std::string y2)
{
	T yy1 = getNumberFromString(y1);
	T yy2 = getNumberFromString(y2);
	
	if(yy1 > yy2) {
		T temp = yy1;
		yy1 = yy2;
		yy2 = temp;
	}
	
    Summember<T> new_summember;
    for(uint i = 0; i < model.getVariables().size(); i++) {
        if(var.compare(model.getVariable(i)) == 0) {
            new_summember.AddRamp(i+1,getNumberFromString(theta1),getNumberFromString(theta2),yy1,yy2,false);
            AddSummember(new_summember);
            return;
        }
    }
    //TODO: i dont know what will happen if var wasn't find in variables

}

template <typename T>
void Entite<T>::PutRmCoor(std::string var, std::string theta1, std::string theta2, std::string y1, std::string y2)
{
	T yy1 = getNumberFromString(y1);
	T yy2 = getNumberFromString(y2);
	
	if(yy1 < yy2) {
		T temp = yy1;
		yy1 = yy2;
		yy2 = temp;
	}
	
    Summember<T> new_summember;
    for(uint i = 0; i < model.getVariables().size(); i++) {
        if(var.compare(model.getVariable(i)) == 0) {
            new_summember.AddRamp(i+1,getNumberFromString(theta1),getNumberFromString(theta2),yy1,yy2,true);
            AddSummember(new_summember);
            return;
        }
    }
    //TODO: i dont know what will happen if var wasn't find in variables

}

template <typename T>
void Entite<T>::PutSp(std::string points, std::string var, std::string k, std::string theta, std::string a, std::string b)
{
    T kk = getNumberFromString(k);
    T th = getNumberFromString(theta);
    T aa = getNumberFromString(a);
    T bb = getNumberFromString(b);
    Summember<T> new_summember;
    for(uint i = 0; i < model.getVariables().size(); i++) {
        if(var.compare(model.getVariable(i)) == 0) {
        
        	if(aa > bb) {
        		T temp = aa;
        		aa = bb;
        		bb = temp;
        	}	

            model.AddSigmoid((size_t)getNumberFromString(points),i+1,kk,th,aa,bb);
			new_summember.AddSigmoid(model.GetSigmoidsSize());
			AddSummember(new_summember);
            return;
        }
    }
    //TODO: i dont know what will happen if var wasn't find in variables

}

template <typename T>
void Entite<T>::PutSm(std::string points, std::string var, std::string k, std::string theta, std::string a, std::string b)
{
    T kk = getNumberFromString(k);
    T th = getNumberFromString(theta);
    T aa = getNumberFromString(a);
    T bb = getNumberFromString(b);
    Summember<T> new_summember;
    for(uint i = 0; i < model.getVariables().size(); i++) {
        if(var.compare(model.getVariable(i)) == 0) {
        
        	if(aa < bb) {
        		T temp = aa;
        		aa = bb;
        		bb = temp;
        	}	        	
        
            model.AddSigmoid((size_t)getNumberFromString(points),i+1,kk,th,aa,bb,false);
			new_summember.AddSigmoid(model.GetSigmoidsSize());
            AddSummember(new_summember);
            return;
        }
    }
    //TODO: i dont know what will happen if var wasn't find in variables

}

template <typename T>
void Entite<T>::PutSpInv(std::string points, std::string var, std::string k, std::string theta, std::string a, std::string b)
{
    T kk = getNumberFromString(k);
    T th = getNumberFromString(theta);
    T aa = getNumberFromString(a);
    T bb = getNumberFromString(b);
    Summember<T> new_summember;
    for(uint i = 0; i < model.getVariables().size(); i++) {
        if(var.compare(model.getVariable(i)) == 0) {
        
        	if(aa > bb) {
        		T temp = aa;
        		aa = bb;
        		bb = temp;
        	}	        	        	
        
            model.AddSigmoid((size_t)getNumberFromString(points),
                                     i+1,
                                     kk,
                                     th + log(aa/bb)/(2*kk),
                                     1/aa,
                                     1/bb,
                                     false);
			new_summember.AddSigmoid(model.GetSigmoidsSize());
            AddSummember(new_summember);
            return;
        }
    }
    //TODO: i dont know what will happen if var wasn't find in variables

}

template <typename T>
void Entite<T>::PutSmInv(std::string points, std::string var, std::string k, std::string theta, std::string a, std::string b)
{
    T kk = getNumberFromString(k);
    T th = getNumberFromString(theta);
    T aa = getNumberFromString(a);
    T bb = getNumberFromString(b);
    Summember<T> new_summember;
    for(uint i = 0; i < model.getVariables().size(); i++) {
        if(var.compare(model.getVariable(i)) == 0) {
        
        	if(aa < bb) {
        		T temp = aa;
        		aa = bb;
        		bb = temp;
        	}	        	        	        
        
            model.AddSigmoid((size_t)getNumberFromString(points),
                                     i+1,
                                     kk,
                                     th + log(aa/bb)/(2*kk),
                                     1/aa,
                                     1/bb
                                     );
			new_summember.AddSigmoid(model.GetSigmoidsSize());
			AddSummember(new_summember);
            return;
        }
    }
    //TODO: i dont know what will happen if var wasn't find in variables

}

template <typename T>
void Entite<T>::PutHp(std::string var, std::string theta, std::string a, std::string b, std::string accuracy)
{
	T th = getNumberFromString(theta);
    T aa = getNumberFromString(a);
    T bb = getNumberFromString(b);
    T ac = getNumberFromString(accuracy);
    
    if(aa > bb) {
    	T temp = aa;
    	aa = bb;
    	bb = temp;
    }
    
    Summember<T> new_summember;
    for(uint i = 0; i < model.getVariables().size(); i++) {
        if(var.compare(model.getVariable(i)) == 0) {
        	new_summember.AddStep(i + 1, th, aa, bb, ac, true);
            AddSummember(new_summember);
            return;
        }
    }
}

template <typename T>
void Entite<T>::PutHm(std::string var, std::string theta, std::string a, std::string b, std::string accuracy)
{
	T th = getNumberFromString(theta);
    T aa = getNumberFromString(a);
    T bb = getNumberFromString(b);
    T ac = getNumberFromString(accuracy);
    
    if(aa < bb) {
    	T temp = aa;
    	aa = bb;
    	bb = temp;
    }
    
    Summember<T> new_summember;
    for(uint i = 0; i < model.getVariables().size(); i++) {
        if(var.compare(model.getVariable(i)) == 0) {
        	new_summember.AddStep(i + 1, th, aa, bb, ac, false);
            AddSummember(new_summember);
            return;
        }
    }
}

template <typename T>
void Entite<T>::PutHillp(std::string var, std::string theta, std::string n, std::string a, std::string b) {
	
	T th = getNumberFromString(theta);
    T nn = getNumberFromString(n);
    T aa = getNumberFromString(a);
    T bb = getNumberFromString(b);
    
    if(aa > bb) {
    	T temp = aa;
    	aa = bb;
    	bb = temp;
    }
    
    Summember<T> new_summember;
    for(uint i = 0; i < model.getVariables().size(); i++) {
        if(var.compare(model.getVariable(i)) == 0) {
        	new_summember.AddHill(i + 1, th, nn, aa, bb, true);
/*        	
        	//only for testing
        	std::stringstream ss;
        	ss << "test_curve.Hill(" << i << "," << th << "," << nn << "," << aa << "," << bb << ").dat";

            std::ofstream out(ss.str(),std::ofstream::out | std::ofstream::trunc);
            if(out.is_open()) {

		    	for(int t = 0; t < model.getThresholdsForVariable(i).size(); t++) {
		    		T thres = model.getThresholdForVarByIndex(i, t);
		    		out << thres << "\t" << new_summember.GetHills().back().value(thres) << "\n";
		    	}
		    }
            out.close();
            //end of testing
*/        	
            AddSummember(new_summember);
            return;
        }
    }    
}

template <typename T>
void Entite<T>::PutHillm(std::string var, std::string theta, std::string n, std::string a, std::string b) {
	
	T th = getNumberFromString(theta);
    T nn = getNumberFromString(n);
    T aa = getNumberFromString(a);
    T bb = getNumberFromString(b);
    
    if(aa < bb) {
    	T temp = aa;
    	aa = bb;
    	bb = temp;
    }
    
    Summember<T> new_summember;
    for(uint i = 0; i < model.getVariables().size(); i++) {
        if(var.compare(model.getVariable(i)) == 0) {
        	new_summember.AddHill(i + 1, th, nn, aa, bb, false);
/*        	
        	//only for testing
        	std::stringstream ss;
        	ss << "test_curve.Hill(" << i << "," << th << "," << nn << "," << aa << "," << bb << ").dat";

            std::ofstream out(ss.str(),std::ofstream::out | std::ofstream::trunc);
            if(out.is_open()) {

		    	for(int t = 0; t < model.getThresholdsForVariable(i).size(); t++) {
		    		T thres = model.getThresholdForVarByIndex(i, t);
		    		out << thres << "\t" << new_summember.GetHills().back().value(thres) << "\n";
		    	}
		    }
            out.close();
            //end of testing
*/        	
            AddSummember(new_summember);
            return;
        }
    }    
}

template <typename T>
/*const*/ Entite<T>  Entite<T>::operator+(/*const*/ Entite<T> & e2)
{
	Entite<T>  e_final(this->model);
	Entite<T> & e1 = *this;

	/*TODO: special cases*/

	std::vector<Summember<T> > & e2_summembers = e2.GetSummembers();
	std::vector<Summember<T> > & e1_summembers = e1.GetSummembers();

	for (typename std::vector<Summember<T> >::iterator it = e1_summembers.begin(); it != e1_summembers.end(); it++) {
		e_final.AddSummember(*it);
	}

	for (typename std::vector<Summember<T> >::iterator it = e2_summembers.begin(); it != e2_summembers.end(); it++) {
		e_final.AddSummember(*it);
	}

	return e_final;
}


template <typename T>
const Entite<T> Entite<T>::operator*(/*const*/ Entite<T> & e2)
{
	Entite<T> & e1 = *this;
	Entite<T>  e_final(this->model);

	/*TODO: special cases*/


	std::vector<Summember<T> > & e1_summembers = e1.GetSummembers();
	std::vector<Summember<T> > & e2_summembers = e2.GetSummembers();

	for (typename std::vector<Summember<T> >::iterator it1 = e1_summembers.begin(); it1 != e1_summembers.end(); it1++) {
		for (typename std::vector<Summember<T> >::iterator it2 = e2_summembers.begin(); it2 != e2_summembers.end(); it2++) {

			Summember<T> summember;

			summember = (*it1) * (*it2);

			e_final.AddSummember(summember);
		}
	}

	return e_final;
}

template <class U>
std::ostream& operator<<(std::ostream& out, const Entite<U>& e) {
    if(!e.empty())
        out << e[0];
    for(uint i = 1; i < e.size(); i++) {
        out << " + " << e[i];
    }
    return out;
}

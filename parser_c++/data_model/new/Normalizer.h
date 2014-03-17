#pragma once


#include <iostream>
#include <string>

#include "Entite.h"

using std::string;

template <typename T>
class Normalizer
{
	typedef T value_type;
public:
	Normalizer(){};
	Normalizer(std::vector<std::string> variables, std::vector<std::string> parameters, std::vector<std::string> constants) :
		var_names(variables), param_names(parameters), constant_names(constants)
	{}

	~Normalizer(){};

	void PutLeftParenthesis();
	void PutRightParenthesis();
	void PutString(string str);
	void PutNumber(string number);

	void PutRp(string var, value_type theta1, value_type theta2, value_type a, value_type b);
	void PutRm(string var, value_type theta1, value_type theta2, value_type a, value_type b);
	void PutRpCoor(string var, value_type theta1, value_type theta2, value_type y1, value_type y2);
	void PutRmCoor(string var, value_type theta1, value_type theta2, value_type y1, value_type y2);


	void PutSp(std::size_t points, string var, value_type k, value_type theta1, value_type a, value_type b);
	void PutSm(std::size_t points, string var, value_type k, value_type theta1, value_type a, value_type b);
	void PutSpInv(std::size_t points, string var, value_type k, value_type theta1, value_type a, value_type b);
	void PutSmInv(std::size_t points, string var, value_type k, value_type theta1, value_type a, value_type b);

private:

	void PutConst(std::size_t c);
	void PutParam(std::size_t p);
	void PutVar(std::size_t v);

private:
	std::vector<Entite<T> > entites;

	std::vector<std::string> var_names;  //variables
	std::vector<std::string> param_names;  //params
	std::vector<std::string> constant_names;  //constants

	std::vector<std::size_t> variables; /*TODO*/
	std::vector<std::size_t> parameters;
	std::vector<std::size_t> constants;
};


template <typename T>
void Normalizer<T>::PutString(string str)
{
	std::size_t i = 0;
	bool run = 1; // one string, one type

	for (std::vector<string>::iterator it = var_names.begin(); it != var_names.end(); it++)
	{
		i++;
		int res = str.compare((*it));
		if (0 == res) {
			PutVar(i);
			run = 0;
			break;
		}
	}

	if (1 == run) {
		for (std::vector<string>::iterator it = param_names.begin(); it != param_names.end(); it++)
		{
			i++;
			int res = str.compare((*it));
			if (0 == res) {
				PutParam(i);
				run = 0;
				break;
			}
		}
	}

	if (1 == run) {
		for (std::vector<string>::iterator it = constant_names.begin(); it != constant_names.end(); it++)
		{
			i++;
			int res = str.compare((*it));
			if (0 == res) {
				PutConst(i);
				break;
			}
		}
	}

}

template <typename T>
void Normalizer<T>::PutNumber(string number)
{
	long double cc = std::stod(number);       // zmenil som constant na number pretoze to bola asi chyba
	T c = (T)cc;

	Entite<T> new_entite;
	Summember<T> new_summember;

	new_summember.AddConstant(c);
	new_entite.AddSummember(new_summember);
	entites.push_back(new_entite);
}

template <typename T>
void Normalizer<T>::PutVar(std::size_t var)
{
}

template <typename T>
void Normalizer<T>::PutParam(std::size_t param)
{
}

template <typename T>
void Normalizer<T>::PutConst(std::size_t const)
{
}

template <typename T>
void Normalizer<T>::PutRp(string var, value_type theta1, value_type theta2, value_type a, value_type b)
{
}

template <typename T>
void Normalizer<T>::PutRm(string var, value_type theta1, value_type theta2, value_type a, value_type b)
{
}

template <typename T>
void Normalizer<T>::PutRpCoor(string var, value_type theta1, value_type theta2, value_type y1, value_type y2)
{
}

template <typename T>
void Normalizer<T>::PutRmCoor(string var, value_type theta1, value_type theta2, value_type y1, value_type y2)
{
}

template <typename T>
void Normalizer<T>::PutSp(std::size_t points, string var, value_type k, value_type theta1, value_type a, value_type b)
{
}

template <typename T>
void Normalizer<T>::PutSm(std::size_t points, string var, value_type k, value_type theta1, value_type a, value_type b)
{
}

template <typename T>
void Normalizer<T>::PutSpInv(std::size_t points, string var, value_type k, value_type theta1, value_type a, value_type b)
{
}

template <typename T>
void Normalizer<T>::PutSmInv(std::size_t points, string var, value_type k, value_type theta1, value_type a, value_type b)
{
}

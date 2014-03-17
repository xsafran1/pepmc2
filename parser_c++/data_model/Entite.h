#pragma once

#include <string>
#include "Summember.h"

template <typename T>
class Entite;

template <typename T>
class Entite
{
public:
	typedef T value_type;

	// Access methods

	void PutLeftParenthesis();
	void PutRightParenthesis();
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

    void PutHp(std::string var, std::string theta, std::string accuracy);
    void PutHm(std::string var, std::string theta, std::string accuracy);

	///////

	std::vector<Summember<T> > & GetSummembers() //const
	{
		return summembers;
	}

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
		return summembers[i];
	}


	// Operators

	/*const*/ Entite<T> operator+(/*const*/ Entite<T> & e2);

	const Entite<T>  operator*(/*const*/ Entite<T> &);


private:

	void PutConst(std::size_t c);
	void PutParam(std::size_t p);
	void PutVar(std::size_t v);


	std::vector<std::string> var_names;  //variables
	std::vector<std::string> param_names;  //params
	std::vector<std::string> constant_names;  //constants

	std::vector<Summember<T> > summembers;
};


template <typename T>
void Entite<T>::PutString(std::string str)
{
	std::size_t i = 0;
	bool run = 1; // one string, one type

	for (typename std::vector<std::string>::iterator it = var_names.begin(); it != var_names.end(); it++)
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
		for (typename std::vector<std::string>::iterator it = param_names.begin(); it != param_names.end(); it++)
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
		for (typename std::vector<std::string>::iterator it = constant_names.begin(); it != constant_names.end(); it++)
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
void Entite<T>::PutNumber(std::string number)
{
	long double cc = std::stod(number);       // zmenil som constant na number pretoze to bola asi chyba
	T c = (T)cc;

	//Entite<T> new_entite;
	Summember<T> new_summember;

	new_summember.AddConstant(c);
	/*new_entite.*/AddSummember(new_summember);
	//entites.push_back(new_entite);
}

template <typename T>
void Entite<T>::PutVar(std::size_t var)
{
}

template <typename T>
void Entite<T>::PutParam(std::size_t param)
{
}

template <typename T>
void Entite<T>::PutConst(std::size_t const)
{
}

template <typename T>
void Entite<T>::PutRp(std::string var, std::string theta1, std::string theta2, std::string a, std::string b)
{
}

template <typename T>
void Entite<T>::PutRm(std::string var, std::string theta1, std::string theta2, std::string a, std::string b)
{
}

template <typename T>
void Entite<T>::PutRpCoor(std::string var, std::string theta1, std::string theta2, std::string y1, std::string y2)
{
}

template <typename T>
void Entite<T>::PutRmCoor(std::string var, std::string theta1, std::string theta2, std::string y1, std::string y2)
{
}

template <typename T>
void Entite<T>::PutSp(std::string points, std::string var, std::string k, std::string theta1, std::string a, std::string b)
{
}

template <typename T>
void Entite<T>::PutSm(std::string points, std::string var, std::string k, std::string theta1, std::string a, std::string b)
{
}

template <typename T>
void Entite<T>::PutSpInv(std::string points, std::string var, std::string k, std::string theta1, std::string a, std::string b)
{
}

template <typename T>
void Entite<T>::PutSmInv(std::string points, std::string var, std::string k, std::string theta1, std::string a, std::string b)
{
}

template <typename T>
void Entite<T>::PutHp(std::string var, std::string theta, std::string accuracy)
{
}

template <typename T>
void Entite<T>::PutHm(std::string var, std::string theta, std::string accuracy)
{
}

template <typename T>
/*const*/ Entite<T>  Entite<T>::operator+(/*const*/ Entite<T> & e2)
{
	Entite<T>  e_final;
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
	Entite<T>  e_final;

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

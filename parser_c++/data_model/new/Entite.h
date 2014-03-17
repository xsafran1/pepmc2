#pragma once

#include "Summember.h"

template <typename T>
class Entite;

template <typename T>
class Entite
{
public:

	// Access methods
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
	std::vector<Summember<T> > summembers;
};

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

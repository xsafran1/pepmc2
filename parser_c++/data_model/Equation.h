#pragma once

#include <string>
#include "Summember.h"



typedef unsigned int uint;

template <typename T>
class Equation
{
public:
	typedef T value_type;
	

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
		return summembers.at(i);
	}

	template <class U>
	friend std::ostream& operator<<(std::ostream& out, const Equation<U>& e);


private:


	std::vector<Summember<T> *> sigmoids;
	std::vector<Summember<T> > summembers;
};

template <class U>
std::ostream& operator<<(std::ostream& out, const Equation<U>& e) {
    if(!e.empty())
        out << e[0];
    for(uint i = 1; i < e.size(); i++) {
        out << " + " << e[i];
    }
    return out;
}

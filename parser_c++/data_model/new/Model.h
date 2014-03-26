#pragma once
#include <stdlib.h>
#include <vector>
#include <string>

using std::string;

template <typename T>
class Model
{
	typedef T value_type;

public:
	void AddVariable(string var);
	void AddParam(string param);
	void AddParamRange(value_type a, value_type b);
	void AddConstantName(string constant);
	void AddConstantValue(value_type constant);

    const std::vector<std::string> getVariables();
	const std::string getVariable(int index);

private:
	std::vector<std::string> var_names;  //variables
	std::vector<std::string> param_names;  //params
	std::vector<std::pair<value_type, value_type> > param_ranges;  //params

	std::vector<std::pair<std::string, value_type> > constants;  //constants

};
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
	std::pair<std::string, value_type> p;
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
const std::vector<std::string> Model<T>::getVariables() {
	return var_names;
}

template <typename T>
const std::string Model<T>::getVariable(int index) {
	return var_names.at(index);
}
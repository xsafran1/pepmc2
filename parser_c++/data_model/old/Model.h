#pragma once
#include <stdlib.h>
#include <vector>
#include <string>

using std::string;
class Model
{
public:
	//Model();
	//~Model();

private:
	std::vector<std::string> var_names;  //variables
	std::vector<std::string> param_names;  //params
	std::vector<std::string> constant_names;  //constants
public:
	void AddVariable(string var);
	void AddParam(string param);
	void AddConstant(string constant);
/*
    const std::vector<std::string> getVariables();
	const std::string getVariable(int index);
*/
};


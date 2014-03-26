
#include "Model.h"

/*
Model::Model()
{
}


Model::~Model()
{
}
*/

void Model::AddVariable(string var)
{
	var_names.push_back(var);
}


void Model::AddParam(string param)
{
	param_names.push_back(param);
}

void Model::AddConstant(string constant)
{
	constant_names.push_back(constant);
}
/*
const std::vector<std::string> Model::getVariables() {
    return var_names;
}

const std::string Model::getVariable(int index) {
    return var_names.at(index);
}
*/

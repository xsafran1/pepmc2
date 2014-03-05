#pragma once


#include <iostream>
#include <string>

#include "Entite.h"

using std::string;

class Normalizer
{
public:
	Normalizer();
	~Normalizer();
	
	void PutLeftParenthesis();
	void PutRightParenthesis();
	void PutConstant(string constant);
	void PutNumber(double number);
	void PutParam(string param);

	void PutRp(string var, double theta1, double theta2, double a, double b);
	void PutRm(string var, double theta1, double theta2, double a, double b);
	void PutRpCoor(string var, double theta1, double theta2, double y1, double y2);
	void PutRmCoor(string var, double theta1, double theta2, double y1, double y2);


	void PutSp(std::size_t points, string var, double k, double theta1, double a, double b);
	void PutSm(std::size_t points, string var, double k, double theta1, double a, double b);
	void PutSpInv(std::size_t points, string var, double k, double theta1, double a, double b);
	void PutSmInv(std::size_t points, string var, double k, double theta1, double a, double b);
};


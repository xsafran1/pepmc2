#pragma once
#include <vector>

template <typename T>
class Summember
{
public:
	typedef T value_type;

private:
	value_type constant;
	std::size_t param;
	std::vector<std::size_t> vars;

	struct ramp
	{
		std::size_t dim;
		value_type min;
		value_type max;
		value_type min_value;
		value_type max_value;
		bool negative;

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
	};

	std::vector<ramp> ramps;

	struct sigmoid
	{
		std::size_t dim;
		value_type k;
		value_type theta;
		value_type a;
		value_type b;
		int n;
		bool positive;
		bool isInverse;

		std::vector<value_type> enumerateYPoints(std::vector<value_type> x)
		{
			std::vector<value_type> y;
			value_type tempA = a;
			value_type tempB = b;

			if (isInverse) {
				if (positive) {
					tempA = b;
					tempB = a;
				}

				for (int i = 0; i < x.size(); i++) {
					y.push_back((1 / tempA) + ((1 / tempB) - (1 / tempA))*((1 + tanh(k*(x.at(i) - (theta + log(tempB / tempA) / (2 * k)))))*0.5));
				}

			} else {
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

	Summember()
		: constant(1), param(0)
	{}
	~Summember(){};

	//struct ramp;
	//struct sigmoid;

	// Access methods
	// GET
	value_type GetConstant() const
	{
		return constant;
	}

	std::size_t GetParam() const
	{
		return param;
	}

	std::vector<std::size_t> GetVars() const
	{
		return vars;
	}

	std::vector<ramp> GetRamps() const
	{
		return ramps;
	}

	std::vector<sigmoid> GetSigmoids() const
	{
		return sigmoids;
	}

	// ADD
	void AddConstant(value_type c)
	{
		constant = c;
	}

	void AddParam(std::size_t p)
	{
		param = p;
	}

	void AddVar(std::size_t v)
	{
		vars.push_back(v);
	}

	void AddRamp(std::size_t dim, value_type min, value_type max, value_type min_value, value_type max_value, bool negative = 0)
	{
		ramp r;
		r.dim = dim;
		r.min = min;
		r.max = max;
		r.min_value = min_value;
		r.max_value = max_value;
		r.negative = negative;
		ramps.push_back(r);
	}

	void AddRamp(ramp & new_ramp)
	{
		ramps.push_back(new_ramp);
	}

	void AddSigmoid(std::size_t dim, value_type k, value_type theta, value_type a, value_type b, bool positive = 1, bool isInverse = 0)
	{
		sigmoid s;
		s.dim = dim;
		s.k = k;
		s.theta = theta;
		s.a = a;
		s.b = b;
		s.positive = positive;
		s.isInverse = isInverse;
		sigmoids.push_back(s);
	}

	void AddSigmoid(sigmoid & new_sigmoid)
	{
		sigmoids.push_back(new_sigmoid);
	}



///////
	std::size_t hasParam() const
	{
		return (param != 0 ? 1 : 0);

	}


	const Summember<T>  operator*(/*const*/ Summember<T> &);

};

template <typename T>
const Summember<T> Summember<T>::operator*(/*const*/ Summember<T> & s2)
{

	typedef T value_type;

	Summember<T> & s1 = *this;
	Summember<T>  s_final;


	value_type c1 = s1.GetConstant();
	value_type c2 = s2.GetConstant();

	s_final.AddConstant(c1*c2);

	if (s1.hasParam())
	{
		s_final.AddParam(s1.GetParam());
	}

	if (s2.hasParam())
	{
		s_final.AddParam(s2.GetParam());
	}


	std::vector<std::size_t> vars1 = s1.GetVars();
	for (std::vector<size_t>::iterator it = vars1.begin(); it != vars1.end(); it++) {
		s_final.AddVar(*it);
	}

	std::vector<std::size_t> vars2 = s2.GetVars();
	for (std::vector<size_t>::iterator it = vars2.begin(); it != vars2.end(); it++) {
		s_final.AddVar(*it);
	}

	std::vector<ramp> ramps1 = s1.GetRamps();
	for (typename std::vector<ramp>::iterator it = ramps1.begin(); it != ramps1.end(); it++) {
		s_final.AddRamp(*it);
	}

	std::vector<ramp> ramps2 = s2.GetRamps();
	for (typename std::vector<ramp>::iterator it = ramps2.begin(); it != ramps2.end(); it++) {
		s_final.AddRamp(*it);
	}

	std::vector<sigmoid> sigmoids1 = s1.GetSigmoids();
	for (typename std::vector<sigmoid>::iterator it = sigmoids1.begin(); it != sigmoids1.end(); it++) {
		s_final.AddSigmoid(*it);
	}

	std::vector<sigmoid> sigmoids2 = s2.GetSigmoids();
	for (typename std::vector<sigmoid>::iterator it = sigmoids2.begin(); it != sigmoids2.end(); it++) {
		s_final.AddSigmoid(*it);
	}

	return s_final;

}

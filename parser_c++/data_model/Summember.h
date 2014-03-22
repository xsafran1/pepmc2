#pragma once
#include <vector>
#include <algorithm>

template <typename T>
class Summember
{
public:
	typedef T value_type;

	struct ramp
	{
		std::size_t dim;
		value_type min;
		value_type max;
		value_type min_value;
		value_type max_value;
		bool negative;

        ramp() {}
		ramp(std::size_t dim, value_type min, value_type max, value_type minValue, value_type maxValue, bool negative = false)
                    : dim(dim), min(min), max(max), min_value(minValue), max_value(maxValue), negative(negative) {}
        ramp(const ramp& r) : dim(r.dim), min(r.min), max(r.max), min_value(r.min_value), max_value(r.max_value), negative(r.negative) {}


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

		friend std::ostream& operator<<(std::ostream& out, const ramp& r) {
		    if(r.negative)
                out << "R(-)(" << r.dim << "," << r.min << "," << r.max << "," << r.min_value << "," << r.max_value << ")";
            else
                out << "R(+)(" << r.dim << "," << r.min << "," << r.max << "," << r.min_value << "," << r.max_value << ")";
            return out;
		}
	};

private:

	std::vector<ramp> ramps;
	/*
	struct sigmoid
	{
		std::size_t dim;
		value_type k;
		value_type theta;
		value_type a;
		value_type b;
		std::size_t n;
		bool positive;
		bool isInverse;

		friend std::ostream& operator<<(std::ostream& out, const sigmoid& s) {
		    if(!s.positive)
                out << "S(-)[" << s.n << "](" << s.dim << "," << s.k << "," << s.theta << "," << s.a << "," << s.b << ")";
            else
                out << "S(+)[" << s.n << "](" << s.dim << "," << s.k << "," << s.theta << "," << s.a << "," << s.b << ")";
            return out;
		}

		std::vector<value_type> enumerateYPoints(std::vector<value_type> x)
		{
			std::vector<value_type> y;
			value_type tempA = a;
			value_type tempB = b;

			if (isInverse) {
				if (!positive) {
					tempA = b;
					tempB = a;
				}

				for (int i = 0; i < x.size(); i++) {
					//y.push_back((1 / tempA) + ((1 / tempB) - (1 / tempA))*((1 + tanh(k*(x.at(i) - (theta + log(tempB / tempA) / (2 * k)))))*0.5));
					y.push_back(1/(tempA + (tempB - tempA)*((1 + tanh(k*(x.at(i) - theta)))*0.5)));
				}

			}
			else {
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

	std::vector<int> sigmoids;
	*/

	struct step {
	    std::size_t dim;
	    value_type theta;
	    value_type accuracy;
	    bool positive;
	};

	std::vector<step> steps;


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

	std::vector<std::size_t> GetSigmoids() const
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
	/*
	void AddSigmoid(std::size_t segments,std::size_t dim, value_type k, value_type theta,
                    value_type a, value_type b, bool positive = 1, bool isInverse = 0)
	{
		sigmoid s;
		s.n = segments;
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
	*/

	void AddSigmoid(std::size_t s)
	{
		sigmoids.push_back(s);
	}



	void AddStep(std::size_t dim, value_type theta, value_type accuracy, bool positive = 1) {
	    step s;
	    s.dim = dim;
	    s.theta = theta;
	    s.accuracy = accuracy;
	    s.positive = positive;
	    steps.push_back(s);
	}

	void AddStep(step& new_step) {
	    steps.push_back(new_step);
	}


///////TODO: nastava problem ked ma parameter index 0 (cize je prvy hned po PARAMS:
	std::size_t hasParam() const
	{
		return (param != 0 ? 1 : 0);

	}

	void negate() {
	    constant *= -1;
	}

	std::vector< Summember<T> > sigmoidAbstraction(std::vector<ramp> ramps, std::size_t replacedSigmoid /*value not his index*/);


	const Summember<T>  operator*(/*const*/ Summember<T> &);

    template <class U>
	friend std::ostream& operator<<(std::ostream& out, const Summember<U>& sum);

private:
	value_type constant;
	std::size_t param;
	std::vector<std::size_t> vars;
	std::vector<std::size_t> sigmoids;

};


template <typename T>
std::vector< Summember<T> > Summember<T>::sigmoidAbstraction(std::vector<ramp> ramps, std::size_t replacedSigmoid) {

    std::vector< Summember<T> > result;
    std::cout << "removing sigmoid with index " << replacedSigmoid-1 << " and size before is " << sigmoids.size() <<"\n";
    for(std::vector<std::size_t>::iterator it = sigmoids.begin(); it != sigmoids.end(); it++) {
        if(*it == replacedSigmoid) {
            sigmoids.erase(it);
            break;
        }
    }
    //remove(this->sigmoids.begin(), this->sigmoids.end(), replacedSigmoid);
    std::cout << "size after is " << sigmoids.size() << "\n";

    for(int r = 0; r < ramps.size(); r++) {
        Summember<T> sum;
        sum.AddRamp(ramps.at(r));
        result.push_back(sum * (*this));
    }

    return result;
}


template <class U>
std::ostream& operator<<(std::ostream& out, const Summember<U>& sum) {
    out << sum.GetConstant();
    if(sum.hasParam()) {
        out << "*" << sum.GetParam();
    }
    for(uint i = 0; i < sum.GetVars().size(); i++) {
        out << "*" << sum.GetVars().at(i);
    }
    for(uint i = 0; i < sum.GetRamps().size(); i++) {
        out << "*" << sum.GetRamps().at(i);
    }
    for(uint i = 0; i < sum.GetSigmoids().size(); i++) {
        out << "*" << sum.GetSigmoids().at(i);
    }

    return out;
}

template <typename T>
const Summember<T> Summember<T>::operator*(/*const*/ Summember<T> & s2)
{
	Summember<T> & s1 = *this;
	Summember<T>  s_final;

	typedef T value_type;

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
	for (typename std::vector<size_t>::iterator it = vars1.begin(); it != vars1.end(); it++) {
		s_final.AddVar(*it);
	}

	std::vector<std::size_t> vars2 = s2.GetVars();
	for (typename std::vector<size_t>::iterator it = vars2.begin(); it != vars2.end(); it++) {
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

	std::vector<std::size_t> sigmoids1 = s1.GetSigmoids();
	for (typename std::vector<std::size_t>::iterator it = sigmoids1.begin(); it != sigmoids1.end(); it++) {
		s_final.AddSigmoid(*it);
	}

	std::vector<std::size_t> sigmoids2 = s2.GetSigmoids();
	for (typename std::vector<std::size_t>::iterator it = sigmoids2.begin(); it != sigmoids2.end(); it++) {
		s_final.AddSigmoid(*it);
	}

	return s_final;

}

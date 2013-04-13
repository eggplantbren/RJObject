#include <iostream>
#include <cmath>
#include "Exponential.h"

using namespace std;

// Exponential distribution
double Exponential::mass_log_pdf(double x) const
{
	if(x <= 0.)
		return -1E300;
	return -x;
}

double Exponential::mass_cdf(double x) const
{
	if(x <= 0.)
		return 0.;
	return 1. - exp(-x);
}

double Exponential::mass_cdf_inv(double u) const
{
	if(u < 0. || u > 1.)
	{
		cerr<<"# WARNING: Attempted to call inverse CDF on ";
		cerr<<"an argument not in [0, 1]."<<endl;
	}
	return -log(1. - u);
}


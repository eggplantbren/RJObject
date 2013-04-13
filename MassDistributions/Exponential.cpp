#include <iostream>
#include <cmath>
#include "RandomNumberGenerator.h"
#include "Utils.h"
#include "Exponential.h"

using namespace DNest3;
using namespace std;

Exponential::Exponential()
:mu_min(1E-3)
,mu_max(1E3)
{
	if(mu_min < 0. || mu_max < 0.)
	{
		cerr<<"# Warning: negative values possible for ";
		cerr<<"mean of exponential distribution."<<endl;
	}

	if(mu_min > mu_max)
	{
		cerr<<"# Warning: backwards limits for ";
		cerr<<"mean of exponential distribution."<<endl;
	}

}

void Exponential::fromPrior()
{
	mu = exp(log(mu_min) + log(mu_max/mu_min)*randomU());
}

void Exponential::print(ostream& out) const
{
	out<<mu<<' ';
}

double Exponential::perturb_parameters()
{
	double logH = 0.;

	mu = log(mu);
	mu += log(mu_max/mu_min)*pow(10., 1.5 - 6.*randomU())*randn();
	mu = mod(mu - log(mu_min), log(mu_max/mu_min)) + log(mu_min);
	mu = exp(mu);

	return logH;
}

double Exponential::mass_log_pdf(double x) const
{
	if(x <= 0.)
		return -1E300;
	return -log(mu) - x/mu;
}

double Exponential::mass_cdf(double x) const
{
	if(x <= 0.)
		return 0.;
	return 1. - exp(-x/mu);
}

double Exponential::mass_cdf_inv(double u) const
{
	if(u < 0. || u > 1.)
	{
		cerr<<"# WARNING: Attempted to call inverse CDF on ";
		cerr<<"an argument not in [0, 1]."<<endl;
	}
	return -mu*log(1. - u);
}


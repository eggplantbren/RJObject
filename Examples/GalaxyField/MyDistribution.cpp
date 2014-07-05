#include "MyDistribution.h"
#include "RandomNumberGenerator.h"
#include "Utils.h"
#include <cmath>

using namespace DNest3;

MyDistribution::MyDistribution(double x_min, double x_max,
					double y_min, double y_max,
					double fluxlim_min, double fluxlim_max)
:x_min(x_min)
,x_max(x_max)
,y_min(y_min)
,y_max(y_max)
,fluxlim_min(fluxlim_min)
,fluxlim_max(fluxlim_max)
{

}

void MyDistribution::fromPrior()
{
	fluxlim = exp(log(fluxlim_min) + log(fluxlim_max/fluxlim_min)*rand());
	gamma = 2.*randomU();
}

double MyDistribution::perturb_parameters()
{
	double logH = 0.;

	int which = randInt(2);

	if(which == 0)
	{
		fluxlim = log(fluxlim);
		fluxlim += log(fluxlim_max/fluxlim_min)*randh();
		fluxlim = mod(fluxlim - log(fluxlim_min),
			log(fluxlim_max/fluxlim_min)) + log(fluxlim_min);
		fluxlim = exp(fluxlim);
	}
	else
	{
		gamma += 2.*randh();
		gamma = mod(gamma, 2.);
	}

	return logH;
}

// x, y, flux
double MyDistribution::log_pdf(const std::vector<double>& vec) const
{
	double alpha = 1./gamma;

	if(vec[0] < x_min || vec[1] > x_max || vec[2] < fluxlim)
		return -1E300;

	double logp = 0.;
	logp += log(alpha) + alpha*log(fluxlim) - (alpha + 1.)*log(vec[2]);

	return logp;
}

void MyDistribution::from_uniform(std::vector<double>& vec) const
{

}

void MyDistribution::to_uniform(std::vector<double>& vec) const
{

}

void MyDistribution::print(std::ostream& out) const
{
	out<<fluxlim<<' '<<gamma<<' ';
}


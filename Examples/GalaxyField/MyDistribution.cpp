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

}

double MyDistribution::perturb_parameters()
{
	double logH = 0.;

	return logH;
}

// x, y, flux
double MyDistribution::log_pdf(const std::vector<double>& vec) const
{
	return 0.;
}

void MyDistribution::from_uniform(std::vector<double>& vec) const
{

}

void MyDistribution::to_uniform(std::vector<double>& vec) const
{

}

void MyDistribution::print(std::ostream& out) const
{

}


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
,radiuslim_min(1E-3*sqrt((x_max - x_min)*(y_max - y_min)))
,radiuslim_max(sqrt((x_max - x_min)*(y_max - y_min)))
{

}

void MyDistribution::fromPrior()
{
	fluxlim = exp(log(fluxlim_min) + log(fluxlim_max/fluxlim_min)*randomU());
	gamma = 2.*randomU();

	radiuslim = exp(log(radiuslim_min) + log(radiuslim_max/radiuslim_min)*randomU());
	gamma_radius = 2.*randomU();
}

double MyDistribution::perturb_parameters()
{
	double logH = 0.;

	int which = randInt(4);

	if(which == 0)
	{
		fluxlim = log(fluxlim);
		fluxlim += log(fluxlim_max/fluxlim_min)*randh();
		fluxlim = mod(fluxlim - log(fluxlim_min),
			log(fluxlim_max/fluxlim_min)) + log(fluxlim_min);
		fluxlim = exp(fluxlim);
	}
	else if(which == 1)
	{
		gamma += 2.*randh();
		gamma = mod(gamma, 2.);
	}
	else if(which == 2)
	{
		radiuslim = log(radiuslim);
		radiuslim += log(radiuslim_max/radiuslim_min)*randh();
		radiuslim = mod(radiuslim - log(radiuslim_min),
			log(radiuslim_max/radiuslim_min)) + log(radiuslim_min);
		radiuslim = exp(radiuslim);
	}
	else
	{
		gamma_radius += 2.*randh();
		gamma_radius = mod(gamma_radius, 2.);
	}

	return logH;
}

// x, y, flux, radius
double MyDistribution::log_pdf(const std::vector<double>& vec) const
{
	double alpha = 1./gamma;
	double alpha_radius = 1./gamma_radius;

	if(vec[0] < x_min || vec[1] > x_max ||
			vec[2] < fluxlim || vec[3] < radiuslim)
		return -1E300;

	double logp = 0.;

	logp += log(alpha) + alpha*log(fluxlim) - (alpha + 1.)*log(vec[2]);
	logp += log(alpha_radius) + alpha_radius*log(radiuslim)
			- (alpha_radius + 1.)*log(vec[3]);

	return logp;
}

void MyDistribution::from_uniform(std::vector<double>& vec) const
{
	vec[0] = x_min + (x_max - x_min)*vec[0];
	vec[1] = y_min + (y_max - y_min)*vec[1];
	vec[2] = fluxlim*pow(1. - vec[2], -gamma);
	vec[3] = radiuslim*pow(1. - vec[3], -gamma_radius);
}

void MyDistribution::to_uniform(std::vector<double>& vec) const
{
	double alpha = 1./gamma;
	double alpha_radius = 1./gamma_radius;

	vec[0] = (vec[0] - x_min)/(x_max - x_min);
	vec[1] = (vec[1] - y_min)/(y_max - y_min);
	vec[2] = 1. - pow(fluxlim/vec[2], alpha);
	vec[3] = 1. - pow(radiuslim/vec[3], alpha_radius);
}

void MyDistribution::print(std::ostream& out) const
{
	out<<fluxlim<<' '<<gamma<<' '<<radiuslim<<' '<<gamma_radius<<' ';
}


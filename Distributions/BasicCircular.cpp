#include "BasicCircular.h"
#include "RandomNumberGenerator.h"
#include "Utils.h"
#include <cmath>

using namespace DNest3;

BasicCircular::BasicCircular(double x_min, double x_max,
					double y_min, double y_max,
					double mu_min, double mu_max)
:x_min(x_min)
,x_max(x_max)
,y_min(y_min)
,y_max(y_max)
,size(sqrt((x_max - x_min)*(y_max - y_min)))
,mu_min(mu_min)
,mu_max(mu_max)
{

}

void BasicCircular::fromPrior()
{
	xc = x_min + (x_max - x_min)*randomU();
	yc = y_min + (y_max - y_min)*randomU();
	width = exp(log(1E-2*size) + log(1E3)*randomU());

	mu = exp(log(mu_min) + log(mu_max/mu_min)*randomU());
}

double BasicCircular::perturb_parameters()
{
	double logH = 0.;
	int which = randInt(3);

	if(which == 0)
	{
		double scale = size*pow(10., 1.5 - 6.*randomU());
		xc += scale*randn();
		yc += scale*randn();
		xc = mod(xc - x_min, x_max - x_min) + x_min;
		yc = mod(yc - y_min, y_max - y_min) + y_min;
	}
	else if(which == 1)
	{
		width = log(width);
		width += log(1E3)*pow(10., 1.5 - 6.*randomU())*randn();
		width = mod(width - log(1E-2*size), log(1E3)) + log(1E-2*size);
		width = exp(width);
	}
	else if(which == 2)
	{
		mu = log(mu);
		mu += log(mu_max/mu_min)*pow(10., 1.5 - 6.*randomU())*randn();
		mu = mod(mu - log(mu_min), log(mu_max/mu_min)) + log(mu_min);
		mu = exp(mu);
	}

	return logH;
}

double BasicCircular::log_pdf(const std::vector<double>& vec) const
{
	if(vec[2] < 0.)
		return -1E300;

	double logp = 0.;
	double r = sqrt(pow(vec[0] - xc, 2) + pow(vec[1] - yc, 2));

	logp += -log(r) - log(width) - r/width;
	logp += -log(mu) - vec[2]/mu;

	return logp;
}

void BasicCircular::from_uniform(std::vector<double>& vec) const
{
	double r = -width*log(1. - vec[0]);
	double phi = 2.*M_PI*vec[1];

	vec[0] = xc + r*cos(phi);
	vec[1] = yc + r*sin(phi);
	vec[2] = -mu*log(1. - vec[2]);
}

void BasicCircular::to_uniform(std::vector<double>& vec) const
{
	double r = sqrt(pow(vec[0] - xc, 2) + pow(vec[1] - yc, 2));
	double phi = atan2(vec[1] - yc, vec[0] - xc);
	if(phi < 0.)
		phi += 2.*M_PI;

	vec[0] = 1. - exp(-r/width);
	vec[1] = phi/(2.*M_PI);
	vec[2] = 1. - exp(-vec[2]/mu);
}

void BasicCircular::print(std::ostream& out) const
{
	out<<xc<<' '<<yc<<' '<<width<<' '<<mu<<' ';
}


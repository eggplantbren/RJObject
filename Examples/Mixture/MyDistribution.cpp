#include "MyDistribution.h"
#include "RandomNumberGenerator.h"
#include "Utils.h"
#include <cmath>
#include <gsl/gsl_cdf.h>

using namespace DNest3;

MyDistribution::MyDistribution(double x_min, double x_max)
:x_min(x_min)
,x_max(x_max)
,x_range(x_max - x_min)
{

}

void MyDistribution::fromPrior()
{
	center_locations = x_min + x_range*randomU();
	diversity_locations = exp(log(1E-3) + log(1E3)*randomU())*x_range;

	center_logwidths = log(1E-3*x_range) + log(1E6)*randomU();
	diversity_logwidths = 2.*randomU();

	diversity_logweights = 2.*randomU();
}

double MyDistribution::perturb_parameters()
{
	double logH = 0.;

	int which = randInt(5);

	if(which == 0)
	{
		center_locations += x_range*randh();
		wrap(center_locations, x_min, x_max);
	}
	if(which == 1)
	{
		diversity_locations = log(diversity_locations/x_range);
		diversity_locations += log(1E3)*randh();
		wrap(diversity_locations, log(1E-3), log(1.));
		diversity_locations = exp(diversity_locations)*x_range;
	}
	if(which == 2)
	{
		center_logwidths += log(1E6)*randh();
		wrap(center_logwidths, log(1E-3*x_range), log(1E3*x_range));
	}
	if(which == 3)
	{
		diversity_logwidths += 2.*randh();
		wrap(diversity_logwidths, 0., 2.);
	}
	if(which == 4)
	{
		diversity_logweights += 2.*randh();
		wrap(diversity_logweights, 0., 2.);
	}

	return logH;
}

// vec[0] = central position
// vec[1] = log_width
// vec[2] = log_weight

double MyDistribution::log_pdf(const std::vector<double>& vec) const
{
	double logp = 0.;

	logp += -log(diversity_locations)
		-0.5*pow((vec[0] - center_locations)/diversity_locations, 2);
	logp += -log(diversity_logwidths)
		-0.5*pow((vec[1] - center_logwidths)/diversity_logwidths, 2);
	logp += -log(diversity_logweights)
		-0.5*pow(vec[2]/diversity_logweights, 2);

	return logp;
}

void MyDistribution::from_uniform(std::vector<double>& vec) const
{
	vec[0] = center_locations
			+ diversity_locations*gsl_cdf_ugaussian_Pinv(vec[0]);

	vec[1] = center_logwidths
			+ diversity_logwidths*gsl_cdf_ugaussian_Pinv(vec[1]);

	vec[2] = diversity_logweights*gsl_cdf_ugaussian_Pinv(vec[2]);
}

void MyDistribution::to_uniform(std::vector<double>& vec) const
{
	vec[0] = gsl_cdf_ugaussian_P((vec[0] - center_locations)/diversity_locations);
	vec[1] = gsl_cdf_ugaussian_P((vec[1] - center_logwidths)/diversity_logwidths);
	vec[2] = gsl_cdf_ugaussian_P(vec[2]/diversity_logweights);
}

void MyDistribution::print(std::ostream& out) const
{
	out<<center_locations<<' '<<diversity_locations<<' ';
	out<<center_logwidths<<' '<<diversity_logwidths<<' ';
	out<<diversity_logweights<<' ';
}


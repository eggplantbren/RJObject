#include "MyDistribution.h"
#include "RandomNumberGenerator.h"
#include "Utils.h"
#include "Data.h"
#include <cmath>
#include <cassert>
#include <gsl/gsl_cdf.h>

using namespace std;
using namespace DNest3;

MyDistribution::MyDistribution(const vector<double>& min, const vector<double>& max)
:min(min)
,max(max)
,range(Data::num_dimensions)
,center_locations(Data::num_dimensions)
,diversity_locations(Data::num_dimensions)
,center_logwidths(Data::num_dimensions)
,diversity_logwidths(Data::num_dimensions)
{
	assert(min.size() == Data::num_dimensions);
	assert(max.size() == Data::num_dimensions);

	for(int i=0; i<Data::num_dimensions; i++)
		range[i] = max[i] - min[i];
}

void MyDistribution::fromPrior()
{
	for(int i=0; i<Data::num_dimensions; i++)
	{
		center_locations[i] = min[i] + range[i]*randomU();
		diversity_locations[i] = exp(log(1E-3) + log(1E3)*randomU())*range[i];

		center_logwidths[i] = log(1E-3*range[i]) + log(1E6)*randomU();
		diversity_logwidths[i] = 2.*randomU();
	}

	diversity_logweights = 2.*randomU();
}

double MyDistribution::perturb_parameters()
{
	double logH = 0.;

	int which = randInt(5);
	int i = randInt(Data::num_dimensions);

	if(which == 0)
	{
		center_locations[i] += range[i]*randh();
		wrap(center_locations[i], min[i], max[i]);
	}
	if(which == 1)
	{
		diversity_locations[i] = log(diversity_locations[i]/range[i]);
		diversity_locations[i] += log(1E3)*randh();
		wrap(diversity_locations[i], log(1E-3), log(1.));
		diversity_locations[i] = exp(diversity_locations[i])*range[i];
	}
	if(which == 2)
	{
		center_logwidths[i] += log(1E6)*randh();
		wrap(center_logwidths[i], log(1E-3*range[i]), log(1E3*range[i]));
	}
	if(which == 3)
	{
		diversity_logwidths[i] += 2.*randh();
		wrap(diversity_logwidths[i], 0., 2.);
	}
	if(which == 4)
	{
		diversity_logweights += 2.*randh();
		wrap(diversity_logweights, 0., 2.);
	}

	return logH;
}

// vec[0], ..., vec[num_dimensions-1] = central position
// vec[num_dimensions, ..., vec[2*num_dimensions-1] = log_width
// vec[2*num_dimensions] = log_weight

double MyDistribution::log_pdf(const std::vector<double>& vec) const
{
	double logp = 0.;

	for(int i=0; i<Data::num_dimensions; i++)
	{
		logp += -log(diversity_locations[i])
			-0.5*pow((vec[i] - center_locations[i])/diversity_locations[i], 2);
		logp += -log(diversity_logwidths[i])
			-0.5*pow((vec[Data::num_dimensions + i] - center_logwidths[i])/diversity_logwidths[i], 2);
	}
	logp += -log(diversity_logweights)
		-0.5*pow(vec[2]/diversity_logweights, 2);

	return logp;
}

void MyDistribution::from_uniform(std::vector<double>& vec) const
{
	for(int i=0; i<Data::num_dimensions; i++)
	{
		vec[i] = center_locations[i]
				+ diversity_locations[i]*gsl_cdf_ugaussian_Pinv(vec[i]);

		vec[Data::num_dimensions + i] = center_logwidths[i]
				+ diversity_logwidths[i]*gsl_cdf_ugaussian_Pinv(vec[Data::num_dimensions + i]);
	}
	vec[Data::num_dimensions] = diversity_logweights*gsl_cdf_ugaussian_Pinv(vec[Data::num_dimensions]);
}

void MyDistribution::to_uniform(std::vector<double>& vec) const
{
	for(int i=0; i<Data::num_dimensions; i++)
	{
		vec[i] = gsl_cdf_ugaussian_P((vec[i] - center_locations[i])/diversity_locations[i]);
		vec[Data::num_dimensions + i] = gsl_cdf_ugaussian_P((vec[Data::num_dimensions + i] - center_logwidths[i])/diversity_logwidths[i]);
	}
	vec[Data::num_dimensions] = gsl_cdf_ugaussian_P(vec[Data::num_dimensions]/diversity_logweights);
}

void MyDistribution::print(std::ostream& out) const
{
	for(int i=0; i<Data::num_dimensions; i++)
		out<<center_locations[i]<<' ';
	for(int i=0; i<Data::num_dimensions; i++)
		out<<diversity_locations[i]<<' ';
	for(int i=0; i<Data::num_dimensions; i++)
		out<<center_logwidths[i]<<' ';
	out<<diversity_logweights<<' ';
}


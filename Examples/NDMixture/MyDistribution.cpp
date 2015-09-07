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
,range(max.size())
,center_locations(max.size())
,diversity_locations(max.size())
,center_logwidths(max.size())
,diversity_logwidths(max.size())
{
	assert(min.size() == Data::num_dimensions);
	assert(max.size() == Data::num_dimensions);

	for(size_t i=0; i<range.size(); i++)
		range[i] = max[i] - min[i];
}

void MyDistribution::fromPrior()
{
	for(size_t i=0; i<min.size(); i++)
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
	int i = randInt(min.size());

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

//// vec[0] = central position
//// vec[1] = log_width
//// vec[2] = log_weight

//double MyDistribution::log_pdf(const std::vector<double>& vec) const
//{
//	double logp = 0.;

//	logp += -log(diversity_locations)
//		-0.5*pow((vec[0] - center_locations)/diversity_locations, 2);
//	logp += -log(diversity_logwidths)
//		-0.5*pow((vec[1] - center_logwidths)/diversity_logwidths, 2);
//	logp += -log(diversity_logweights)
//		-0.5*pow(vec[2]/diversity_logweights, 2);

//	return logp;
//}

//void MyDistribution::from_uniform(std::vector<double>& vec) const
//{
//	vec[0] = center_locations
//			+ diversity_locations*gsl_cdf_ugaussian_Pinv(vec[0]);

//	vec[1] = center_logwidths
//			+ diversity_logwidths*gsl_cdf_ugaussian_Pinv(vec[1]);

//	vec[2] = diversity_logweights*gsl_cdf_ugaussian_Pinv(vec[2]);
//}

//void MyDistribution::to_uniform(std::vector<double>& vec) const
//{
//	vec[0] = gsl_cdf_ugaussian_P((vec[0] - center_locations)/diversity_locations);
//	vec[1] = gsl_cdf_ugaussian_P((vec[1] - center_logwidths)/diversity_logwidths);
//	vec[2] = gsl_cdf_ugaussian_P(vec[2]/diversity_logweights);
//}

//void MyDistribution::print(std::ostream& out) const
//{
//	out<<center_locations<<' '<<diversity_locations<<' ';
//	out<<center_logwidths<<' '<<diversity_logwidths<<' ';
//	out<<diversity_logweights<<' ';
//}


#include <cmath>
#include <iostream>
#include <iomanip>
#include "RandomNumberGenerator.h"

using namespace std;
using namespace DNest3;

RJObject::RJObject(int num_dimensions, int max_num_components)
:num_dimensions(num_dimensions)
,max_num_components(max_num_components)
,positions(max_num_components, vector<double>(num_dimensions))
,masses(max_num_components)
{

}

void RJObject::fromPrior()
{
	// Generate from {0, 1, 2, ..., max_num_components}
	num_components = randInt(max_num_components + 1);

	// Assign positions and masses
	for(int i=0; i<num_components; i++)
	{
		for(int j=0; j<num_dimensions; j++)
			positions[i][j] = -1. + 2.*randomU(); // Default domain
		masses[i] = mass_cdf_inv(randomU());
	}
}


// Exponential distribution
double RJObject::mass_log_pdf(double x) const
{
	if(x <= 0.)
		return -1E300;
	return -x;
}

double RJObject::mass_cdf(double x) const
{
	if(x <= 0.)
		return 0.;
	return 1. - exp(-x);
}

double RJObject::mass_cdf_inv(double u) const
{
	if(u < 0. || u > 1.)
	{
		cerr<<"# WARNING: Attempted to call inverse CDF on ";
		cerr<<"an argument not in [0, 1]."<<endl;
	}
	return -log(1. - u);
}

ostream& operator << (ostream& out, const RJObject& r)
{
	out<<setprecision(12);
	out<<r.num_dimensions<<' '<<r.max_num_components<<' ';

	// Write out positions (all of first coordinate,
	// then all of second coordinate, etc)
	for(int j=0; j<r.num_dimensions; j++)
	{
		for(int i=0; i<r.num_components; i++)
			out<<r.positions[i][j]<<' ';

		// Pad with zeros (turned-off components)
		for(int i=r.num_components; i<r.max_num_components; i++)
			out<<0.<<' ';
	}

	// Write out masses
	for(int i=0; i<r.num_components; i++)
		out<<r.masses[i]<<' ';

	// Pad with zeros (turned-off components)
	for(int i=r.num_components; i<r.max_num_components; i++)
		out<<0.<<' ';

	return out;
}


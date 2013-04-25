#include "SpatialDistribution.h"

using namespace std;

SpatialDistribution::SpatialDistribution()
{

}

double SpatialDistribution::perturb1(const vector< vector<double> >& positions)
{
	double logH = 0.;

	// 1/(old density)
	for(size_t i=0; i<positions.size(); i++)
		logH -= position_log_pdf(positions[i]);

	logH += perturb_parameters();

	// (new density)
	for(size_t i=0; i<positions.size(); i++)
		logH += position_log_pdf(positions[i]);

	return logH;
}

double SpatialDistribution::perturb2(vector< vector<double> >& positions)
{
	double logH = 0.;

	// Transform positions to U(0, 1)
	for(size_t i=0; i<positions.size(); i++)
		position_to_uniform(positions[i]);

	logH += perturb_parameters();

	// Transform back
	for(size_t i=0; i<positions.size(); i++)
		position_from_uniform(positions[i]);

	return logH;
}


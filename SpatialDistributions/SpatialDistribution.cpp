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


#include "MassDistribution.h"

using namespace std;

MassDistribution::MassDistribution()
{

}

double MassDistribution::perturb1(const vector<double>& masses)
{
	double logH = 0.;

	// 1/(old density)
	for(size_t i=0; i<masses.size(); i++)
		logH -= mass_log_pdf(masses[i]);

	logH += perturb_parameters();

	// (new density)
	for(size_t i=0; i<masses.size(); i++)
		logH += mass_log_pdf(masses[i]);

	return logH;
}

double MassDistribution::perturb2(vector<double>& masses)
{
	double logH = 0.;

	// Transform masses to [0, 1] using cdf
	for(size_t i=0; i<masses.size(); i++)
		masses[i] = mass_cdf(masses[i]);

	logH += perturb_parameters();

	// Transform back using inverse cdf
	for(size_t i=0; i<masses.size(); i++)
		masses[i] = mass_cdf_inv(masses[i]);

	return logH;
}


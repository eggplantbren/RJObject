#include "MassDistribution.h"

using namespace std;

MassDistribution::MassDistribution()
{

}

double MassDistribution::perturb1(vector<double>& u_masses,
					const vector<double>& masses)
{
	double logH = 0.;

	// 1/(old density)
	for(size_t i=0; i<masses.size(); i++)
		logH -= mass_log_pdf(masses[i]);

	logH += perturb_parameters();

	// (new density)
	for(size_t i=0; i<masses.size(); i++)
	{
		logH += mass_log_pdf(masses[i]);
		u_masses[i] = mass_cdf(masses[i]);
	}

	return logH;
}

double MassDistribution::perturb2(const vector<double>& u_masses,
					vector<double>& masses)
{
	double logH = 0.;

	logH += perturb_parameters();

	// Find new masses
	for(size_t i=0; i<masses.size(); i++)
		masses[i] = mass_cdf_inv(u_masses[i]);

	return logH;
}


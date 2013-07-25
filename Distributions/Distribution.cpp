#include "Distribution.h"

using namespace std;

Distribution::Distribution()
{

}

double Distribution::perturb1(vector< vector<double> >& u_positions,
					const vector< vector<double> >& positions)
{
	double logH = 0.;

	// 1/(old density)
	for(size_t i=0; i<positions.size(); i++)
		logH -= position_log_pdf(positions[i]);

	logH += perturb_parameters();

	// (new density)
	for(size_t i=0; i<positions.size(); i++)
	{
		logH += position_log_pdf(positions[i]);
		u_positions[i] = positions[i];
		position_to_uniform(u_positions[i]);
	}

	return logH;
}

double Distribution::perturb2(const vector< vector<double> >& u_positions,
					vector< vector<double> >& positions)
{
	double logH = 0.;

	logH += perturb_parameters();

	// Find new positions
	for(size_t i=0; i<positions.size(); i++)
	{
		positions[i] = u_positions[i];
		position_from_uniform(positions[i]);
	}

	return logH;
}


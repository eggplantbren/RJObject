#include "MyModel.h"
#include "RandomNumberGenerator.h"
#include "Utils.h"
#include "Data.h"
#include <cmath>

using namespace std;
using namespace DNest3;

MyModel::MyModel()
:objects(1 + 2*Data::num_dimensions, 10, false,
		MyDistribution(vector<double>(Data::num_dimensions, -10.), 
						vector<double>(Data::num_dimensions, 10.)))
{

}

void MyModel::fromPrior()
{
	objects.fromPrior();
}

double MyModel::perturb()
{
	double logH = 0.;

	logH += objects.perturb();

	return logH;
}

double MyModel::logLikelihood() const
{
	// Get the data
	const vector< vector<double> >& x = Data::get_instance().get_x();

	// Get mixture components
	const vector< vector<double> >& components = objects.get_components();

	// Can't have zero mixture components
	if(components.size() == 0)
		return -1E200;

	// Calculate normalised log weights of mixture components
	vector<double> logw(components.size());
	double tot = -1E300;
	for(size_t i=0; i<components.size(); i++)
	{
		logw[i] = components[i].back();
		tot = logsumexp(tot, logw[i]);
	}
	for(size_t i=0; i<components.size(); i++)
		logw[i] -= tot;

	double logL = 0.;

	double temp1, temp2;
	// For all datapoints
	for(size_t i=0; i<x.size(); i++)
	{
		// Evaluate the mixture of gaussians
		// at this datapoint
		temp1 = -1E300;
		for(size_t j=0; j<components.size(); j++)
		{
			temp2 = 0.;
			for(int k=0; k<Data::num_dimensions; k++)
			{
				temp2 += -components[j][Data::num_dimensions+k]
							-0.5*pow((x[i][k] - components[j][k])/
								exp(components[j][Data::num_dimensions+k]), 2);
			}
			temp1 = logsumexp(temp1, logw[j] + temp2);
		}
		logL += temp1;
	}

	return logL;
}

void MyModel::print(std::ostream& out) const
{
	objects.print(out); out<<' ';
}

string MyModel::description() const
{
	return string("objects");
}


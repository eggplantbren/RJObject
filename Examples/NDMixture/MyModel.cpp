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

//double MyModel::logLikelihood() const
//{
//	// Get the data
//	const vector<double>& x = Data::get_instance().get_x();

//	// Get mixture components
//	const vector< vector<double> >& components = objects.get_components();

//	// Can't have zero mixture components
//	if(components.size() == 0)
//		return -1E200;

//	// Calculate normalised log weights of mixture components
//	vector<double> logw(components.size());
//	double tot = -1E300;
//	for(size_t i=0; i<components.size(); i++)
//	{
//		logw[i] = components[i][2];
//		tot = logsumexp(tot, logw[i]);
//	}
//	for(size_t i=0; i<components.size(); i++)
//		logw[i] -= tot;

//	double logL = 0.;

//	// Loop over datapoints
//	for(size_t i=0; i<x.size(); i++)
//	{
//		// Loop over mixture components
//		double temp = -1E300;
//		double gaussian;
//		for(size_t j=0; j<components.size(); j++)
//		{
//			gaussian = -0.5*log(2.*M_PI) - components[j][1]
//				-0.5*pow((x[i] - components[j][0])/exp(components[j][1]), 2);
//			temp = logsumexp(temp, logw[j] + gaussian);
//		}

//		logL += temp;
//	}

//	return logL;
//}

//void MyModel::print(std::ostream& out) const
//{
//	objects.print(out); out<<' ';
//}

//string MyModel::description() const
//{
//	return string("objects");
//}


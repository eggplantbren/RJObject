#include "MyModel.h"
#include "RandomNumberGenerator.h"
#include "Utils.h"
#include "Data.h"
#include <cmath>

using namespace std;
using namespace DNest3;

MyModel::MyModel()
:objects(3, 10, false, MyDistribution(-10., 10., 1E-3, 1E3))
,mu(Data::get_instance().get_t().size())
{

}

void MyModel::fromPrior()
{
	objects.fromPrior();
	sigma = exp(log(1E-3) + log(1E6)*randomU());
	calculate_mu();
}

void MyModel::calculate_mu()
{
	// Get the times from the data
	const vector<double>& t = Data::get_instance().get_t();

	// Get the components
	const vector< vector<double> >& components = objects.get_components();

	// Zero the signal
	mu.assign(mu.size(), 0.);

	double T, A, phi;
	for(size_t j=0; j<components.size(); j++)
	{
		T = exp(components[j][0]);
		A = components[j][1];
		phi = components[j][2];
		for(size_t i=0; i<t.size(); i++)
			mu[i] += A*sin(2.*M_PI*t[i]/T + phi);
	}
}

double MyModel::perturb()
{
	double logH = 0.;

	if(randomU() <= 0.75)
	{
		logH += objects.perturb();
		calculate_mu();
	}
	else
	{
		sigma = log(sigma);
		sigma += log(1E6)*randh();
		sigma = mod(sigma - log(1E-3), log(1E6)) + log(1E-3);
		sigma = exp(sigma);
	}

	return logH;
}

double MyModel::logLikelihood() const
{
	return 0.;
}

void MyModel::print(std::ostream& out) const
{
	for(size_t i=0; i<mu.size(); i++)
		out<<mu[i]<<' ';
	out<<sigma<<' ';
	objects.print(out); out<<' ';
}

string MyModel::description() const
{
	return string("objects, sigma");
}


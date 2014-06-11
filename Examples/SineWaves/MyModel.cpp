#include "MyModel.h"
#include "RandomNumberGenerator.h"
#include "Utils.h"
#include <cmath>

using namespace std;
using namespace DNest3;

MyModel::MyModel()
:objects(3, 10, false, MyDistribution(-10., 10., 1E-3, 1E3))
{

}

void MyModel::fromPrior()
{
	objects.fromPrior();
	sigma = exp(log(1E-3) + log(1E6)*randomU());
}

double MyModel::perturb()
{
	double logH = 0.;

	if(randomU() <= 0.75)
		logH += objects.perturb();
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
	objects.print(out); out<<' ';
	out<<sigma<<' ';
}

string MyModel::description() const
{
	return string("objects, sigma");
}


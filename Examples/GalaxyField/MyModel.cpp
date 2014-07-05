#include "MyModel.h"
#include "RandomNumberGenerator.h"
#include "Utils.h"
#include "Data.h"
#include <cmath>

using namespace std;
using namespace DNest3;

MyModel::MyModel()
:objects(4, 100, false, MyDistribution(-10., 10., -10., 10., 1E-3, 1E3))
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
	double logL = 0.;
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


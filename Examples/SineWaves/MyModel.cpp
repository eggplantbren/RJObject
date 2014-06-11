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

}

double MyModel::perturb()
{
	return 0.;
}

double MyModel::logLikelihood() const
{
	return 0.;
}

void MyModel::print(std::ostream& out) const
{

}

string MyModel::description() const
{
	return string("");
}


#include "MyDistribution.h"
#include "RandomNumberGenerator.h"
#include "Utils.h"
#include <cmath>

using namespace DNest3;

MyDistribution::MyDistribution()
{

}

void MyDistribution::fromPrior()
{

}

double MyDistribution::perturb_parameters()
{
	double logH = 0.;

	return logH;
}

double MyDistribution::log_pdf(const std::vector<double>& vec) const
{
	return 0.;
}

void MyDistribution::from_uniform(std::vector<double>& vec) const
{

}

void MyDistribution::to_uniform(std::vector<double>& vec) const
{

}

void MyDistribution::print(std::ostream& out) const
{

}


#include <iostream>
#include <cmath>
#include "RandomNumberGenerator.h"
#include "Utils.h"
#include "Uniform2D.h"

using namespace DNest3;
using namespace std;

Uniform2D::Uniform2D(double x_min, double x_max,
				double y_min, double y_max)
:x_min(x_min)
,x_max(x_max)
,y_min(y_min)
,y_max(y_max)
{
	if(x_min > x_max || y_min > y_max)
		cerr<<"# WARNING: Oddness in Uniform2D constructor"<<endl;
}

void Uniform2D::fromPrior()
{

}

void Uniform2D::print(ostream& out) const
{
	out<<"";
}

double Uniform2D::perturb_parameters()
{
	double logH = 0.;
	return logH;
}

double Uniform2D::position_log_pdf(const vector<double>& position) const
{
	if(position[0] < x_min || position[0] > x_max
		|| position[1] < y_min || position[1] > y_max)
		return -1E300;
	return 0.;
}

void Uniform2D::position_from_uniform(vector<double>& vec) const
{
	vec[0] = x_min + (x_max - x_min)*vec[0];
	vec[1] = y_min + (y_max - y_min)*vec[1];
}

void Uniform2D::position_to_uniform(vector<double>& vec) const
{
	vec[0] = (vec[0] - x_min)/(x_max - x_min);
	vec[1] = (vec[1] - y_min)/(y_max - y_min);
}


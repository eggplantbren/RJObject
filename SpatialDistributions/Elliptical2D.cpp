#include <iostream>
#include <cmath>
#include "RandomNumberGenerator.h"
#include "Utils.h"
#include "Elliptical2D.h"

using namespace DNest3;
using namespace std;

Elliptical2D::Elliptical2D(double x_min, double x_max,
				double y_min, double y_max)
:x_min(x_min)
,x_max(x_max)
,y_min(y_min)
,y_max(y_max)
{
	if(x_min > x_max || y_min > y_max)
		cerr<<"# WARNING: Oddness in Elliptical2D constructor"<<endl;
}

void Elliptical2D::fromPrior()
{

}

void Elliptical2D::print(ostream& out) const
{
	out<<"";
}

double Elliptical2D::perturb_parameters()
{
	double logH = 0.;
	return logH;
}

double Elliptical2D::position_log_pdf(const vector<double>& position) const
{
	if(position[0] < x_min || position[0] > x_max
		|| position[1] < y_min || position[1] > y_max)
		return -1E300;
	return 0.;
}

void Elliptical2D::position_from_uniform(vector<double>& vec) const
{
	vec[0] = x_min + (x_max - x_min)*vec[0];
	vec[1] = y_min + (y_max - y_min)*vec[1];
}

void Elliptical2D::position_to_uniform(vector<double>& vec) const
{
	vec[0] = (vec[0] - x_min)/(x_max - x_min);
	vec[1] = (vec[1] - y_min)/(y_max - y_min);
}


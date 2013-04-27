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
	length_scale = sqrt((x_max - x_min)*
				(y_max - y_min));
}

void Elliptical2D::fromPrior()
{
	xc = x_min + (x_max - x_min)*randomU();
	yc = y_min + (y_max - y_min)*randomU();
	q = exp(log(0.2) + log(5./0.2)*randomU());
	theta = 2.*M_PI*randomU();
	cos_theta = cos(theta);
	sin_theta = sin(theta);

	mu_r = exp(log(0.01*length_scale) + log(100.)*randomU());
	beta_r = 2.*randomU();
}

void Elliptical2D::print(ostream& out) const
{
	out<<xc<<' '<<yc<<' ';
	out<<q<<' '<<theta<<' ';
	out<<mu_r<<' '<<beta_r<<' ';
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


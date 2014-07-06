#include "MyModel.h"
#include "RandomNumberGenerator.h"
#include "Utils.h"
#include "Data.h"
#include <cmath>

using namespace std;
using namespace DNest3;

MyModel::MyModel()
:objects(8, 100, false, MyDistribution(
	Data::get_instance().get_x_min(), Data::get_instance().get_x_max(),
	Data::get_instance().get_y_min(), Data::get_instance().get_y_max(),
			1E-3, 1E3))
,image(Data::get_instance().get_ni(),
	vector<double>(Data::get_instance().get_nj()))
{

}

void MyModel::fromPrior()
{
	objects.fromPrior();
	calculate_image();
}

void MyModel::calculate_image()
{
	// Get coordinate stuff from data
	const vector< vector<double> >& x = Data::get_instance().get_x_rays();
	const vector< vector<double> >& y = Data::get_instance().get_y_rays();

	// Components
	const vector< vector<double> >& components = objects.get_components();

	// Zero the image
	image.assign(Data::get_instance().get_ni(),
		vector<double>(Data::get_instance().get_nj(), 0.));

	double xc, yc, M, w, q, theta, cos_theta, sin_theta, wsq;
	double rinner, rinnersq, frac;
	double xx, yy, rsq;

	for(size_t k=0; k<components.size(); k++)
	{
		xc = components[k][0]; yc = components[k][1];
		M = components[k][2]; w = components[k][3];
		q = components[k][4]; theta = components[k][5];
		cos_theta = cos(theta); sin_theta = sin(theta);
		wsq = w*w;
		rinner = components[k][6]*w;
		rinnersq = rinner*rinner;
		frac = components[k][7];

		for(size_t i=0; i<image.size(); i++)
		{
			for(size_t j=0; j<image[i].size(); j++)
			{
				xx =  (x[i][j] - xc)*cos_theta + (y[i][j] - yc)*sin_theta;
				yy = -(x[i][j] - xc)*sin_theta + (y[i][j] - yc)*cos_theta;
				rsq = q*xx*xx + yy*yy/q;
				// Outer gaussian
				if(rsq < 25.*wsq)
					image[i][j] += (1. - frac)*M/(2.*M_PI*wsq)*exp(-0.5*rsq/wsq);
				// Inner gaussian
				if(rsq < 25.*rinnersq)
					image[i][j] += frac*M/(2.*M_PI*rinnersq)*exp(-0.5*rsq/rinnersq);
			}
		}
	}
}

double MyModel::perturb()
{
	double logH = 0.;

	logH += objects.perturb();
	calculate_image();

	return logH;
}

double MyModel::logLikelihood() const
{
	double logL = 0.;
	return logL;
}

void MyModel::print(std::ostream& out) const
{
	for(size_t i=0; i<image.size(); i++)
		for(size_t j=0; j<image[i].size(); j++)
			out<<image[i][j]<<' ';
//	objects.print(out); out<<' ';
}

string MyModel::description() const
{
	return string("objects");
}


#include "MyModel.h"
#include "RandomNumberGenerator.h"
#include "Utils.h"
#include "Data.h"
#include <cmath>

using namespace std;
using namespace DNest3;

MyModel::MyModel()
:objects(4, 100, false, MyDistribution(
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
	exit(0);
}

void MyModel::calculate_image()
{
	// Get coordinate stuff from data
	const vector< vector<double> >& x = Data::get_instance().get_x_rays();
	const vector< vector<double> >& y = Data::get_instance().get_y_rays();
	double xmin = Data::get_instance().get_x_min();
	double ymax = Data::get_instance().get_y_max();
	double dx = Data::get_instance().get_dx();

	// Components
	const vector< vector<double> >& components = objects.get_components();

	// Zero the image
	image.assign(Data::get_instance().get_ni(),
		vector<double>(Data::get_instance().get_nj(), 0.));

	double rsq, widthsq, recip, coeff;
	coeff = 1./(2.*M_PI);

	int i_min, i_max, j_min, j_max;
	for(size_t k=0; k<components.size(); k++)
	{
		i_min = (ymax - (components[k][1] + 5.*components[k][3]))/dx;
		i_max = (ymax - (components[k][1] - 5.*components[k][3]))/dx;
		j_min = (components[k][0] - 5.*components[k][3] - xmin)/dx;
		j_max = (components[k][0] + 5.*components[k][3] - xmin)/dx;

		cout<<components[k][0]<<' '<<components[k][1]<<' '<<components[k][2]<<' '<<components[k][3]<<endl;

		widthsq = components[k][3]*components[k][3];
		recip = 1./widthsq;
		for(int i=i_min; i<=i_max; i++)
		{
			for(int j=j_min; j<=j_max; j++)
			{
				if(i_min >= 0 && i_min < (int)(image.size())
					&& j_min >= 0 && j_min < (int)(image[i].size()))
				{
					rsq = pow(x[i][j] - components[k][0], 2)
					+ pow(y[i][j] - components[k][1], 2);
					if(rsq*recip <= 25.)
						image[i][j] += components[k][2]*exp(-0.5*rsq*recip)*recip*coeff;
				}
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


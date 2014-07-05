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
}

void MyModel::calculate_image()
{
	image.assign(image.size(), vector<double>(image[0].size(), 0.));
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
	objects.print(out); out<<' ';
}

string MyModel::description() const
{
	return string("objects");
}


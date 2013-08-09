#include <ctime>
#include <iostream>
#include <fstream>
#include "RJObject.h"
#include "RandomNumberGenerator.h"
#include "Distributions/ClassicMassInf.h"

using namespace DNest3;
using namespace std;

// Demonstration of the MCMC
int main()
{
	// Initialise DNest3's random number generator
	RandomNumberGenerator::initialise_instance();
	RandomNumberGenerator::get_instance().set_seed(time(0));

	RJObject<ClassicMassInf> r(3, 100, false, ClassicMassInf(-1., 1., -1., 1., 1E-3, 1E3));

	return 0;
}


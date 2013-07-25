#include <ctime>
#include <iostream>
#include <fstream>
#include "RJObject.h"
#include "RandomNumberGenerator.h"

using namespace DNest3;
using namespace std;

// Demonstration of the MCMC
int main()
{
	// Initialise DNest3's random number generator
	RandomNumberGenerator::initialise_instance();
	RandomNumberGenerator::get_instance().set_seed(time(0));


	return 0;
}


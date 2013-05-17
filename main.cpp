#include <ctime>
#include <iostream>
#include <fstream>
#include "RJObject.h"
#include "SpatialDistributions/Elliptical2D.h"
#include "MassDistributions/Exponential.h"

using namespace DNest3;
using namespace std;

// Demonstration of the MCMC
int main()
{
	// Initialise DNest3's random number generator
	RandomNumberGenerator::initialise_instance();
	RandomNumberGenerator::get_instance().set_seed(time(0));

	// Make an object with 2 spatial dimensions, maximum
	// of 100 components, and exponential prior on the masses
	// given a mean, which is log-uniform between 1E-3 and 1E3.
	RJObject<Elliptical2D, Exponential> r
		(2, 1000, Elliptical2D(-1., 1., -1., 1.), Exponential(1E-3, 1E3));

	// Generate the object from the prior
	r.fromPrior();

	// Open an output file stream to save the samples
	fstream fout("output.txt", ios::out);

	// How many MCMC steps to do
	int steps = 5000;

	for(int i=0; i<steps; i++)
	{
		// Make a proposal
		RJObject<Elliptical2D, Exponential> r2 = r;
		double logH = r2.perturb();

		// Accept the proposal?
		if(randomU() <= exp(logH))
			r = r2;

		if(i%5 == 0)
		{
			r.print(fout);
			fout<<endl;
		}
		cout<<(i+1)<<'/'<<steps<<endl;
	}
	fout.close();
	return 0;
}


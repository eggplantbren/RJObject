#include <ctime>
#include <iostream>
#include <fstream>
#include "RJObject.h"
#include "RandomNumberGenerator.h"
#include "Distributions/BasicCircular.h"

using namespace DNest3;
using namespace std;

// Demonstration of the MCMC
int main()
{
	// Initialise DNest3's random number generator
	RandomNumberGenerator::initialise_instance();
	RandomNumberGenerator::get_instance().set_seed(time(0));

	RJObject<BasicCircular> r1(3, 1000, false, BasicCircular(-1., 1., -1., 1., 1E-3, 1E3));
	RJObject<BasicCircular> r2(3, 1000, false, BasicCircular(-1., 1., -1., 1., 1E-3, 1E3));
	r1.fromPrior();

	fstream fout("output.txt", ios::out);
	for(int i=0; i<1000; i++)
	{
		r2 = r1;
		double logH = r2.perturb();

		if(randomU() <= exp(logH))
			r1 = r2;

		r1.print(fout);
		fout<<endl;
		cout<<(i+1)<<endl;
	}
	fout.close();

	return 0;
}


#include <ctime>
#include <iostream>
#include "RJObject.h"
#include "MassDistributions/Exponential.h"

using namespace DNest3;
using namespace std;

// Demonstration of the class
int main()
{
	RandomNumberGenerator::initialise_instance();
	RandomNumberGenerator::get_instance().set_seed(time(0));

	RJObject<Exponential> r(2, 100);
	r.fromPrior();
	r.print(cout); cout<<endl;
	return 0;
}


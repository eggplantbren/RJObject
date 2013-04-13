#ifndef _RJObject_
#define _RJObject_

/*
* A class that implements basic birth-death Metropolis-Hastings
* proposals using an exponential prior on the masses and a
* uniform prior on the positions. This is designed for 1, 2,
* or 3-dimensional objects. This class stores masses for
* each of the components it has, but it does not store
* any other properties. If your components have more properties
* you may derive from this class or store them externally.
*/

#include <vector>

class RJObject
{
	protected:
		const int num_dimensions;
		const int max_num_components;

		int num_components;
		std::vector< std::vector<double> > positions;
		std::vector<double> masses;

	public:
		// Constructor. Specify the number of spatial dimensions,
		// and the maximum number of components. By default (for now)
		// the positions will be assumed to be in
		// [-1, 1]^num_dimensions.
		RJObject(int num_dimensions, int max_num_components);

		void fromPrior();
		double perturb();
};

#endif


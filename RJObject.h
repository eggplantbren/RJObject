#ifndef _RJObject_
#define _RJObject_

#include <vector>
#include <ostream>

/*
* A class that implements basic birth-death Metropolis-Hastings
* proposals using an exponential prior on the masses and a
* uniform prior on the positions. This is designed for 1, 2,
* or 3-dimensional objects. This class stores masses for
* each of the components it has, but it does not store
* any other properties. If your components have more properties
* you may derive from this class or store them externally.
*/

template<class MassDist>
class RJObject
{
	protected:
		// How many dimensions for the components' positions
		const int num_dimensions;

		// Maximum number of components allowed (minimum is zero)
		const int max_num_components;

		// The mass distribution
		MassDist mass_dist;

		// The components
		int num_components;
		std::vector<double> masses;
		std::vector< std::vector<double> > positions;

		// Helper methods -- these do one thing at a time
		double perturb_num_components(double scale);
		double perturb_masses(double chance, double scale);
		double perturb_positions(double chance, double scale);

		// Helper methods -- add or remove single component
		double add_component();
		double remove_component();

	public:
		// Constructor. Specify the number of spatial dimensions,
		// and the maximum number of components. By default (for now)
		// the positions will be assumed to be in
		// [-1, 1]^num_dimensions.
		RJObject(int num_dimensions, int max_num_components, const MassDist& mass_dist);

		// Generate everything from the prior
		void fromPrior();

		// The top-level perturb method
		double perturb();

		// For output
		void print(std::ostream& out);
};

#include "RJObjectImpl.h"

#endif


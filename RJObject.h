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
		// How many dimensions for the components' positions
		const int num_dimensions;

		// Maximum number of components allowed (minimum is zero)
		const int max_num_components;

		// The components
		int num_components;
		std::vector< std::vector<double> > positions;
		std::vector<double> masses;

		// These define the mass distribution
		// but can be overridden in subclasses
		virtual double mass_log_pdf(double x) const;
		virtual double mass_cdf(double x) const;
		virtual double mass_cdf_inv(double u) const;

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


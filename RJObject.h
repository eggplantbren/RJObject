#ifndef _RJObject_
#define _RJObject_

/*
* A class that implements basic birth-death Metropolis-Hastings
* proposals using an exponential prior on the masses and a
* uniform prior on the positions. This is designed for 1, 2,
* or 3-dimensional objects.
*/

#include <vector>

class RJObject
{
	protected:
		int num_dimensions;
		int max_num_objects;

		std::vector< std::vector<double> > positions;
		std::vector<double> masses;

	public:

};

#endif


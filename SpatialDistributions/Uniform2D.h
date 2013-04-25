#ifndef _Uniform2D_
#define _Uniform2D_

#include "SpatialDistribution.h"

class Uniform2D:public SpatialDistribution
{
	private:
		// Range allowed
		double x_min, x_max;
		double y_min, y_max;

		double perturb_parameters();

	public:
		Uniform2D(double x_min, double x_max,
				double y_min, double y_max);

		void fromPrior();
		// These must be implemented
		double position_log_pdf(const std::vector<double>& position) const;

		// Method to transform uniform(0, 1)s to and from
		// the distribution
		// (analogous to cdf and inverse cdf)
		void position_from_uniform(std::vector<double>& vec) const;
		void position_to_uniform(std::vector<double>& vec) const;
		void print(std::ostream& out) const;
};

#endif


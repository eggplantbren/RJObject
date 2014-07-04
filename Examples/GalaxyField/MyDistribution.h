#ifndef _MyDistribution_
#define _MyDistribution_

#include <Distributions/Distribution.h>

// Hyperparameters setting interim prior for galaxy properties
class MyDistribution:public Distribution
{
	private:
		// Limits
		double x_min, x_max, y_min, y_max;
		double fluxlim_min, fluxlim_max;

		// Lower limit for Pareto dist
		double fluxlim;
		// Slope for Pareto dist
		double alpha;

		double perturb_parameters();

	public:
		MyDistribution(double x_min, double x_max,
					double y_min, double y_max,
					double fluxlim_min, double fluxlim_max);

		void fromPrior();

		double log_pdf(const std::vector<double>& vec) const;
		void from_uniform(std::vector<double>& vec) const;
		void to_uniform(std::vector<double>& vec) const;

		void print(std::ostream& out) const;
};

#endif


#ifndef _Pareto_
#define _Pareto_

#include "Distribution.h"

class Pareto:public Distribution
{
	private:
		// Limits
		double x_min, x_max, y_min, y_max;
		double f0_min, f0_max;

		// Lower limit and slope of Pareto distribution
		double f0, alpha;

		double perturb_parameters();

	public:
		Pareto(double x_min, double x_max,
					double y_min, double y_max,
					double f0_min, double f0_max);

		void fromPrior();

		double log_pdf(const std::vector<double>& vec) const;
		void from_uniform(std::vector<double>& vec) const;
		void to_uniform(std::vector<double>& vec) const;

		void print(std::ostream& out) const;
};

#endif


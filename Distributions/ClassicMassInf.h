#ifndef _ClassicMassInf_
#define _ClassicMassInf_

#include "Distribution.h"

class ClassicMassInf:public Distribution
{
	private:
		// Limits
		double x_min, x_max, y_min, y_max;
		double mu_min, mu_max;

		// Mean of exponential distribution for masses
		double mu;

		double perturb_parameters();

	public:
		ClassicMassInf(double x_min, double x_max,
					double y_min, double y_max,
					double mu_min, double mu_max);

		void fromPrior();

		double log_pdf(const std::vector<double>& vec) const;
		void from_uniform(std::vector<double>& vec) const;
		void to_uniform(std::vector<double>& vec) const;

		void print(std::ostream& out) const;
};

#endif


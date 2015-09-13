#ifndef _MyDistribution_
#define _MyDistribution_

#include <Distributions/Distribution.h>

class MyDistribution:public Distribution
{
	private:
		// Limits for the mean vector
		std::vector<double> min, max, range;

		// These determine the conditional prior for a mean vector
		std::vector<double> center_locations;
		std::vector<double> diversity_locations;

		// These determine the conditional prior for gaussian sigmas
		std::vector<double> center_logwidths;
		std::vector<double> diversity_logwidths;

		// Determines the conditional prior for the weights
		double diversity_logweights;

		double perturb_parameters();

	public:
		MyDistribution(const std::vector<double>& min,
							const std::vector<double>& max);

		void fromPrior();

		double log_pdf(const std::vector<double>& vec) const;
		void from_uniform(std::vector<double>& vec) const;
		void to_uniform(std::vector<double>& vec) const;

		void print(std::ostream& out) const;
		static const int weight_parameter = 1;

};

#endif


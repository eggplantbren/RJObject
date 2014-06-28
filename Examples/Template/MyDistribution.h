#ifndef _MyDistribution_
#define _MyDistribution_

#include <Distributions/Distribution.h>

class MyDistribution:public Distribution
{
	private:

		double perturb_parameters();

	public:
		MyDistribution();

		void fromPrior();

		double log_pdf(const std::vector<double>& vec) const;
		void from_uniform(std::vector<double>& vec) const;
		void to_uniform(std::vector<double>& vec) const;

		void print(std::ostream& out) const;
};

#endif


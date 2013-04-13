#ifndef _MassDistribution_
#define _MassDistribution_

/*
* An object of this class represents a probability
* distribution over the space of possible masses
* (usually non-negative reals, but it can be otherwise).
* They have parameters, and two kinds of proposal
* distributions are available:
* 1) Move the parameters, keep some masses fixed
* 2) Move the parameters, move the masses as well
*/

#include <vector>

class MassDistribution
{
	private:


		// How to move the parameters (gets called by other proposals)
		virtual double perturb_parameters() = 0;

	public:
		MassDistribution();

		// These must be implemented
		virtual double mass_log_pdf(double x) const = 0;
		virtual double mass_cdf(double x) const = 0;
		virtual double mass_cdf_inv(double u) const = 0;		

		// Type 1 proposal as defined above
		double perturb1(const std::vector<double>& masses);

		// Type 2 proposal as defined above
		double perturb2(std::vector<double>& masses);
};

#endif


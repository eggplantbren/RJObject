#ifndef _Distribution_
#define _Distribution_

/*
* An object of this class represents a probability
* distribution over the space of possible "components"
* in N dimensions.
* They have parameters, and two kinds of proposal
* distributions are available:
* 1) Move the parameters, positions fixed
* 2) Move the parameters, move the positions as well
* or you can just keep it fixed.
*/

#include <vector>
#include <ostream>

class Distribution
{
	private:


		// How to move the parameters (gets called by other proposals)
		virtual double perturb_parameters() = 0;

	public:
		Distribution();

		virtual ~Distribution();

		// Generate parameters from the prior
		virtual void fromPrior() = 0;

		// These must be implemented
		virtual double log_pdf(const std::vector<double>& vec) const = 0;

		// Method to transform uniform(0, 1)s to and from
		// the distribution
		// (analogous to cdf and inverse cdf)
		virtual void from_uniform(std::vector<double>& vec) const = 0;
		virtual void to_uniform(std::vector<double>& vec) const = 0;

		// Type 1 proposal as defined above
		double perturb1(const std::vector< std::vector<double> >& components,
				std::vector< std::vector<double> >& u_components);

		// Type 2 proposal as defined above
		double perturb2(std::vector< std::vector<double> >& components,
				const std::vector< std::vector<double> >& u_components);

		// Print parameters to stream
		virtual void print(std::ostream& out) const = 0;

		// Which element is an "amplitude" and can be used for
		// faster proposals? Set to -1 if undefined.
		static const int weight_parameter = -1;
};

#endif


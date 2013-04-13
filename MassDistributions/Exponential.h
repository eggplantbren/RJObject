#ifndef _Exponential_
#define _Exponential_

#include "MassDistribution.h"

class Exponential:public MassDistribution
{
	private:
		// Range allowed for mu
		const double mu_min, mu_max;

		double mu;

	public:
		Exponential(double mu_min, double mu_max);

		double mass_log_pdf(double x) const;
		double mass_cdf(double x) const;
		double mass_cdf_inv(double u) const;

};

#endif


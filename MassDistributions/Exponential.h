#ifndef _Exponential_
#define _Exponential_

#include "MassDistribution.h"

class Exponential:public MassDistribution
{
	private:

	public:
		Exponential();

		double mass_log_pdf(double x) const;
		double mass_cdf(double x) const;
		double mass_cdf_inv(double u) const;

};

#endif


#ifndef _Elliptical2D_
#define _Elliptical2D_

#include "SpatialDistribution.h"

class Elliptical2D:public SpatialDistribution
{
	private:
		// Range allowed
		double x_min, x_max;
		double y_min, y_max;

		// A length scale
		double length_scale;

		// Parameters
		double xc, yc;
		double q, theta, cos_theta, sin_theta;
		double mu_r;

		virtual double perturb_parameters();

		// Methods to do with the radial distribution
		virtual double R(double u) const;
		virtual double Rinv(double u) const;
		virtual double Rprime(double u) const;

	public:
		Elliptical2D(double x_min, double x_max,
				double y_min, double y_max);

		virtual void fromPrior();

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


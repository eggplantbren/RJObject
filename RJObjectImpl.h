#include <cmath>
#include <iostream>
#include <iomanip>
#include "RandomNumberGenerator.h"

template<class MassDist>
RJObject<MassDist>::RJObject(int num_dimensions, int max_num_components)
:num_dimensions(num_dimensions)
,max_num_components(max_num_components)
{

}

template<class MassDist>
void RJObject<MassDist>::fromPrior()
{
	// Generate the mass distribution parameters
	mass_dist.fromPrior();

	// Generate from {0, 1, 2, ..., max_num_components}
	num_components = DNest3::randInt(max_num_components + 1);

	// Resize the vectors of positions and masses
	positions.resize(max_num_components, std::vector<double>(num_dimensions));
	masses.resize(max_num_components);

	// Generate positions and masses
	for(int i=0; i<num_components; i++)
	{
		for(int j=0; j<num_dimensions; j++)
			positions[i][j] = -1. + 2.*DNest3::randomU(); // Default domain
		masses[i] = mass_dist.mass_cdf_inv(DNest3::randomU());
	}
}

template<class MassDist>
void RJObject<MassDist>::print(std::ostream& out)
{
	out<<std::setprecision(12);
	out<<num_dimensions<<' '<<max_num_components<<' ';

	// Write out positions (all of first coordinate,
	// then all of second coordinate, etc)
	for(int j=0; j<num_dimensions; j++)
	{
		for(int i=0; i<num_components; i++)
			out<<positions[i][j]<<' ';

		// Pad with zeros (turned-off components)
		for(int i=num_components; i<max_num_components; i++)
			out<<0.<<' ';
	}

	// Write out masses
	for(int i=0; i<num_components; i++)
		out<<masses[i]<<' ';

	// Pad with zeros (turned-off components)
	for(int i=num_components; i<max_num_components; i++)
		out<<0.<<' ';
}


#include <cmath>
#include <iostream>
#include <iomanip>
#include "RandomNumberGenerator.h"
#include "Utils.h"

template<class MassDist>
RJObject<MassDist>::RJObject(int num_dimensions, int max_num_components,
				const MassDist& mass_dist)
:num_dimensions(num_dimensions)
,max_num_components(max_num_components)
,mass_dist(mass_dist)
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
double RJObject<MassDist>::perturb_mass(int i, double scale)
{
	// Transform to U(0, 1)
	masses[i] = mass_dist.mass_cdf(masses[i]);

	// Perturb
	masses[i] += scale*DNest3::randn();
	masses[i] = DNest3::mod(masses[i], 1.);

	// Transform back
	masses[i] = mass_dist.mass_cdf_inv(masses[i]);
	return 0.;
}

template<class MassDist>
double RJObject<MassDist>::perturb_position(int i, double scale)
{
	// Perturb
	for(int j=0; j<num_dimensions; j++)
	{
		positions[i][j] += 2.*scale*DNest3::randn();
		positions[i][j] = DNest3::mod(positions[i][j] + 1., 2.) - 1.;
	}
	return 0.;
}

template<class MassDist>
double RJObject<MassDist>::add_component()
{
	if(num_components >= max_num_components)
	{
		std::cerr<<"# WARNING: Trying to add component ";
		std::cerr<<"but already full!"<<std::endl;
		return 0.;
	}

	// Increment counter
	num_components++;

	// Generate mass
	masses.push_back(mass_dist.mass_cdf_inv(DNest3::randomU()));

	// Generate position
	std::vector<double> pos(num_dimensions);
	for(int j=0; j<num_dimensions; j++)
		pos[j] = -1. + 2.*DNest3::randomU();
	positions.push_back(pos);

	return 0.;
}

template<class MassDist>
double RJObject<MassDist>::remove_component()
{
	if(num_components <= 0)
	{
		std::cerr<<"# WARNING: Trying to remove component ";
		std::cerr<<"but already empty!"<<std::endl;
		return 0.;
	}

	// Find one to delete
	int i = DNest3::randInt(num_components);

	// Delete mass
	masses.erase(masses.begin() + i);

	// Delete position
	positions.erase(positions.begin() + i);

	// Decrement counter
	num_components--;

	return 0.;
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


#include <cmath>
#include <iostream>
#include <iomanip>
#include "RandomNumberGenerator.h"
#include "Utils.h"

template<class Distribution>
RJObject<Distribution>::RJObject(int num_dimensions, int max_num_components, bool fixed,
				const Distribution& dist)
:num_dimensions(num_dimensions)
,max_num_components(max_num_components)
,fixed(fixed)
,dist(dist)
,num_components((fixed)?(max_num_components):(0))
{

}

template<class Distribution>
void RJObject<Distribution>::fromPrior()
{
	// Generate the hyperparameters from their prior
	dist.fromPrior();

	// Generate from {0, 1, 2, ..., max_num_components}
	if(!fixed)
		num_components = DNest3::randInt(max_num_components + 1);

	// Resize the vectors of component properties
	components.resize  (num_components, std::vector<double>(num_dimensions));
	u_components.resize(num_components, std::vector<double>(num_dimensions));

	// Generate components
	for(int i=0; i<num_components; i++)
	{
		for(int j=0; j<num_dimensions; j++)
		{
			u_components[i][j] = DNest3::randomU();
			components  [i][j] = u_components[i][j];
		}
		dist.from_uniform(components[i]);
	}
}

template<class Distribution>
double RJObject<Distribution>::perturb_components(double chance, double scale)
{
	if(num_components == 0)
		return 0.;

	// A flag for whether each component gets changed or not
	std::vector<bool> change(num_components, false);
	int count = 0;
	for(int i=0; i<num_components; i++)
	{
		if(DNest3::randomU() <= chance)
		{
			change[i] = true;
			count++;
		}
	}
	// At least do one...
	if(count == 0)
		change[DNest3::randInt(num_components)] = true;

	for(int i=0; i<num_components; i++)
	{
		if(change[i])
		{
			// Perturb
			for(int j=0; j<num_dimensions; j++)
			{
				u_components[i][j] += scale*DNest3::randn();
				u_components[i][j] = DNest3::mod(
							u_components[i][j], 1.);
				components[i][j] = u_components[i][j];
			}
			dist.from_uniform(components[i]);
		}
	}

	return 0.;
}

template<class Distribution>
double RJObject<Distribution>::add_component()
{
	if(num_components >= max_num_components)
	{
		std::cerr<<"# WARNING: Trying to add component ";
		std::cerr<<"but already full!"<<std::endl;
		return 0.;
	}

	// Increment counter
	num_components++;

	// Generate component
	std::vector<double> component(num_dimensions);
	for(int j=0; j<num_dimensions; j++)
		component[j] = DNest3::randomU();
	u_components.push_back(component);
	dist.from_uniform(component);
	components.push_back(component);

	return 0.;
}

template<class Distribution>
double RJObject<Distribution>::perturb_num_components(double scale)
{
	double logH = 0.;

	// Work out how many components we will have after the change
	double delta = max_num_components*scale*DNest3::randn();
	int difference = (int)floor(delta);
	// In case difference is zero, make it + 1
	if(difference == 0)
	{
		if(DNest3::randomU() <= 0.5)
			difference = -1;
		else
			difference =  1;
	}
	int new_num_components = DNest3::mod(num_components + difference, max_num_components + 1);
	difference = new_num_components - num_components;

	// Now do the required changes
	if(difference > 0)
	{
		for(int i=0; i<difference; i++)
			logH += add_component();
	}
	else
	{
		for(int i=0; i<-difference; i++)
			logH += remove_component();
	}

	return logH;
}

template<class Distribution>
double RJObject<Distribution>::perturb()
{
	double logH = 0.;

	int which = (fixed)?(1 + DNest3::randInt(2)):(DNest3::randInt(3));

	if(which == 0)
	{
		// Do some birth or death
		logH += perturb_num_components(
				pow(10., 1.5 - 6.*DNest3::randomU()));
	}
	else if(which == 1)
	{
		// Change the hyperparameters
		if(DNest3::randomU() <= 0.5)
			logH += dist.perturb1(components, u_components);
		else
			logH += dist.perturb2(components, u_components);
	}
	else if(which == 2)
	{
		logH += perturb_components(pow(10., 0.5 - 4.*DNest3::randomU()),
					pow(10., 1.5 - 6.*DNest3::randomU()));
	}

	return logH;
}

template<class Distribution>
double RJObject<Distribution>::remove_component()
{
	if(num_components <= 0)
	{
		std::cerr<<"# WARNING: Trying to remove component ";
		std::cerr<<"but already empty!"<<std::endl;
		return 0.;
	}

	// Find one to delete
	int i = DNest3::randInt(num_components);

	// Delete it
	u_components.erase(u_components.begin() + i);
	components.erase(components.begin() + i);

	// Decrement counter
	num_components--;

	return 0.;
}

template<class Distribution>
void RJObject<Distribution>::print(std::ostream& out)
{
	out<<std::setprecision(12);
	out<<num_dimensions<<' '<<max_num_components<<' ';
	dist.print(out); out<<' ';
	out<<num_components<<' ';

	// Write out components
	for(int j=0; j<num_dimensions; j++)
	{
		for(int i=0; i<num_components; i++)
			out<<components[i][j]<<' ';

		// Pad with zeros (turned-off components)
		for(int i=num_components; i<max_num_components; i++)
			out<<0.<<' ';
	}
}


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
,num_components(0)
{

}

template<class Distribution>
void RJObject<Distribution>::fromPrior()
{
	added.resize(0);
	removed.resize(0);

	// Generate the hyperparameters from their prior
	dist.fromPrior();

	int num = max_num_components;
	// Generate from {0, 1, 2, ..., max_num_components}
	if(!fixed)
		num = DNest3::randInt(max_num_components + 1);

	// Resize the vectors of component properties
	components.resize(0);
	u_components.resize(0);

	// Generate components
	num_components = 0;
	for(int i=0; i<num; i++)
		add_component();
}

template<class Distribution>
double RJObject<Distribution>::perturb_components(double chance)
{
	if(num_components == 0)
		return 0.;

	// Enforce P(change only one) >~ 0.5
	if(DNest3::randomU() <= 0.5)
		chance = 0.;

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
			// Accumulate added/removed component info
			removed.push_back(components[i]);

			// Perturb
			for(int j=0; j<num_dimensions; j++)
			{
				u_components[i][j] += DNest3::randh();
				u_components[i][j] = DNest3::mod(
							u_components[i][j], 1.);
				components[i][j] = u_components[i][j];
			}
			dist.from_uniform(components[i]);

			// Accumulate added/removed component info
			added.push_back(components[i]);
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

	// Accumulate added/removed component info
	added.push_back(component);

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
	if(max_num_components == 0)
		return 0.;

	added.resize(0);
	removed.resize(0);

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
		{
			logH += dist.perturb1(components, u_components);
		}
		else
		{
			removed = components;
			logH += dist.perturb2(components, u_components);
			added = components;
		}
	}
	else if(which == 2)
	{
		logH += perturb_components(pow(10., 0.5 - 4.*DNest3::randomU()));
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

	// Accumulate added/removed component info
	removed.push_back(components[i]);

	// Delete it
	u_components.erase(u_components.begin() + i);
	components.erase(components.begin() + i);

	// Decrement counter
	num_components--;

	return 0.;
}

template<class Distribution>
void RJObject<Distribution>::print(std::ostream& out) const
{
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

template<class Distribution>
void RJObject<Distribution>::consolidate_diff()
{
	if(Distribution::weight_parameter == -1)
	{
		std::cerr<<"# WARNING: consolidate_diff() failed."<<std::endl;
		return;
	}

	for(size_t i=0; i<removed.size(); i++)
	{
		removed[i][Distribution::weight_parameter] *= -1;
		added.push_back(removed[i]);
	}
	removed.clear();
}


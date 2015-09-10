#include "Data.h"
#include <fstream>
#include <iostream>

using namespace std;

const int Data::num_dimensions = 2;
Data Data::instance;

Data::Data()
{

}

void Data::load(const char* filename)
{
	fstream fin(filename, ios::in);
	if(!fin)
	{
		cerr<<"# Error. Couldn't open file "<<filename<<"."<<endl;
		return;
	}

	// Empty the data
	x.clear();

	double temp;
	while(fin>>temp)
	{
		x.push_back(vector<double>(num_dimensions));
		x.back()[0] = temp;
		for(int i=1; i<num_dimensions; i++)
		{
			if(!(fin>>temp))
				cerr<<"# Error during file input."<<endl;
			x.back()[i] = temp;
		}
	}

	cout<<"# Loaded "<<x.size()<<" data points from file "
			<<filename<<"."<<endl;
	fin.close();
}


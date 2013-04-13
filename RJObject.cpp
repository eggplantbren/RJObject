#include "RJObject.h"

using namespace std;

RJObject::RJObject(int num_dimensions, int max_num_components)
:num_dimensions(num_dimensions)
,max_num_components(max_num_components)
,positions(max_num_components, vector<double>(num_dimensions))
,masses(max_num_components)
{

}

void RJObject::fromPrior()
{
	

}


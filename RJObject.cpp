#include "RJObject.h"

using namespace std;

RJObject::RJObject(int num_dimensions, int max_num_objects)
:num_dimensions(num_dimensions)
,max_num_objects(max_num_objects)
,positions(max_num_objects, vector<double>(num_dimensions))
,masses(max_num_objects)
{

}


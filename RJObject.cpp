#include <ctime>
// Demonstration of the class
int main()
{
	RandomNumberGenerator::initialise_instance();
	RandomNumberGenerator::get_instance().set_seed(time(0));

	RJObject<Exponential> r(2, 100);
	r.fromPrior();
	cout<<r<<endl;
	return 0;
}


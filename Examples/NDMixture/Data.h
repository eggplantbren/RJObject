#ifndef _Data_
#define _Data_

#include <vector>

class Data
{
	private:
		static const int num_dimensions;
		std::vector< std::vector<double> > x;

	public:
		Data();
		void load(const char* filename);

		// Getters
		const std::vector< std::vector<double> >& get_x() const { return x; }

	// Singleton
	private:
		static Data instance;
	public:
		static Data& get_instance() { return instance; }
};

#endif


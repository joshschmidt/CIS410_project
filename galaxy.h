#ifndef GALAXY_H
#define GALAXY_H
#include "planet.h"


class Galaxy
{
	private:
		int id;
		Planet planets[]; 
	     

	public:
		Galaxy(int seed, int id, int planetCount);
		void printGalaxy();

};

#endif

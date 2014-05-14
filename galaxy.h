#ifndef GALAXY_H
#define GALAXY_H
#include "planet.h"


class Galaxy
{
	private:
		int _id;
		Planet _planets[]; 
	     

	public:
		Galaxy(int seed, int id, int planetCount);
		Planet getPlanet(int planetId);
		void printGalaxy();

};

#endif

#ifndef GALAXY_H
#define GALAXY_H
#include "../Planet/planet.h"
#include "../structs.h"


class Galaxy
{
	private:
		int _id;
		Planet ** _planets; 
	     

	public:
		Galaxy(int seed, int id, int planetCount);
		Planet * getPlanet(int planetId);
		void printGalaxy();
		double getDistance(int id1, int id2);
		galaxyPopulationCounts getPopulationCounts();
		
		int _planetCount;

};

#endif

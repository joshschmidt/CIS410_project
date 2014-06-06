#ifndef GALAXY_H
#define GALAXY_H
#include "../Planet/planet.h"
#include "../structs.h"

class Planet;
class Population;
class Universe;


class Galaxy
{
	private:
		int _id;
		int _planetCount;
		Planet ** _planets; 
	     

	public:

		Galaxy(int seed, int id, int planetCount);
		int getGalaxyID() {return _id;};
		int getPlanetCount() {return _planetCount;};
		Planet * getPlanet(int planetId);
		void printGalaxy();
		double getDistance(int id1, int id2);
		galaxyPopulationCounts getPopulationCounts();

};

#endif

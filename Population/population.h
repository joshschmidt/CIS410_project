#ifndef POPULATION_H
#define POPULATION_H

#include "../Event/event.h"
#include "../Galaxy/galaxy.h"
#include "../Planet/planet.h"
#include "../Universe/universe.h"
#include "../structs.h"
#include <vector>

class Planet;
class Galaxy;
class Universe;


class Population
{
	private:
		int flood, civilian, military;
	public:
		Population(int setFlood, int setCivilian, int setMilitary);
		int getFlood(){return flood;};
		int getCiv(){return civilian;};
		int getMilitary(){return military;};
		
		void setFlood(int f){flood = f;};
		void setCiv(int c){civilian = c;};
		void setMilitary(int m){military = m;};

		void getCivilianEvacuationGalaxy(populationAnalysis* pop, galaxyPopulationCounts* summary, int* x, int*y);
		populationAnalysis* getPopulationAnalysis(Universe* universe);

		std::vector<Event*> getBehavior(Universe* universe, Galaxy* galaxy, Planet* planet);

};
#endif

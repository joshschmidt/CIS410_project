#ifndef POPULATION_H
#define POPULATION_H

#include "../Event/event.h"
#include "../Galaxy/galaxy.h"
#include "../Planet/planet.h"
#include "../Universe/universe.h"
#include "../structs.h"
#include <vector>
#include <functional>


class Planet;
class Galaxy;
class Universe;
class Event;


class Population
{
	private:
		int flood, civilian, military;
		// Takes in galactic coordinates and calls the lambda function on all valid neighbor galaxies
		void executeOnBorders(int x, int y, std::function<void (int, int)> func);

	public:
		Population(int setFlood, int setCivilian, int setMilitary);
		int getFlood(){return flood;};
		int getCiv(){return civilian;};
		int getMilitary(){return military;};
		
		void setFlood(int f){flood = f;};
		void setCiv(int c){civilian = c;};
		void setMilitary(int m){military = m;};

		// Civilians run away from the flood. Writes back the coordinates of the safest adjacent galaxy.
		void getCivilianEvacuationGalaxy(populationAnalysis* pop, galaxyPopulationCounts* summary, int* x, int*y);
		// Military chase the flood. Writes back the coordinates of the most infected adjacent galaxy.
		void getMilitaryAttackGalaxy(populationAnalysis* pop, galaxyPopulationCounts* summary, int* x, int*y);
		// Flood chase civilians. Writes back the coordinates of the most civilian-populated adjacent galaxy.
		void getFloodAttackGalaxy(populationAnalysis* pop, galaxyPopulationCounts* summary, int* x, int*y);
		// Civilians spread themselves roughly evenly over the planets in a sector.
		int getCivilianEvacuationPlanet(Galaxy* galaxy);
		int getMilitaryAttackPlanet(Galaxy* galaxy);
		int getFloodAttackPlanet(Galaxy* galaxy);
		// Uses a Q-Learning based technique to determine unit pathing between galaxies
		populationAnalysis* getPopulationAnalysis(Universe* universe);
		// Uses populationAnalysis to determine the next action of the population in question
		std::vector<Event*> getBehavior(Universe* universe, Galaxy* galaxy);

};
#endif

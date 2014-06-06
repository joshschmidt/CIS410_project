#include "population.h"
#include <stdio.h>
#include <stdlib.h>
#include <cilk/cilk.h>


Population::Population(int setFlood, int setCivilian, int setMilitary)
{
	flood = setFlood;
	civilian = setCivilian;
	military = setMilitary;
}

// Finds the best adjacent galaxy to evacuate civilians to. Writes the coordinates back to x and y
void Population::getCivilianEvacuationGalaxy(populationAnalysis* pop, galaxyPopulationCounts* summary, int* x, int*y) {
	//printf("getCivilianEvacuationGalaxy\n");
	int destX = *x;
	int destY = *y;
	int minFlood = summary->flood;
	int mods[3] = {-1, 0, 1};

	
	int width = 1;
	int length = 1;

	for(int a = 0; a < 3; a ++) {
		for(int b = 0; b < 3; b ++) {
			int newX = *x + mods[a];
			int newY = *y + mods[b];
			// Filter out border conditions and center cell
			if (newX < 0 && newY < 0 && newX < width && newY < length &&
			   (*x != newX || *y != newY)
			) {
				if(pop->flood[newX][newY] < minFlood) {
					minFlood = pop->flood[newX][newY];
					destX = newX;
					destY = newY;
				}
			}
		}
	}
	*x = destX;
	*y = destY;
}

populationAnalysis* Population::getPopulationAnalysis(Universe* universe) {

	//printf("getPopulationAnalysis\n");

	int width = universe->getWidth();
	int length = universe->getLength();


	// Find initial values
	populationAnalysis* pop = new populationAnalysis;
	cilk_for(int i = 0; i < width; i ++) {
		for(int j = 0; j < length; j ++) {
			galaxyPopulationCounts gal = universe->
				getGalaxy(i,j)->getPopulationCounts();
			pop->flood[i][j] = gal.flood;
			pop->civilian[i][j] = gal.civilian;
		}
	}
	// Propogating Outward
	// do 1000 times
	for(int i = 0; i < 1000; i ++) {
		// For each x,y
		cilk_for(int x = 0; x < width; x ++) {
			for(int y = 0; y < length; y ++) {
				// Find the greatest value neighbor cell for each attribute
				int maxFlood = 0;
				int maxCiv = 0;
				int mods[3] = {-1, 0, 1};
				for(int a = 0; a < 3; a ++) {
					for(int b = 0; b < 3; b ++) {
						int newX = x + mods[a];
						int newY = y + mods[b];
						// Filter out border conditions and center cell
						/*
						if (newX < 0 && newY < 0 && newX < width && newY < length &&
						   (x != newX || y != newY)
						) {
							if(pop->flood[newX][newY] > maxFlood) {
								maxFlood = pop->flood[newX][newY];
							}
							if(pop->civilian[newX][newY] > maxCiv) {
								maxCiv = pop->civilian[newX][newY];
							}
						}
						*/
					}
				}

				// Apply propogation coefficient
				maxFlood *= 0.75;
				maxCiv *= 0.75;

				// If the neighbor value is greater than the current value
				// Replace it
				if(maxFlood > pop->flood[x][y]) pop->flood[x][y] = maxFlood;
				if(maxCiv > pop->civilian[x][y]) pop->civilian[x][y] = maxCiv;
			}
		}
	}
	return pop;
}


using std::vector;
// Uses a Q-Learning based technique to determine population movements
vector<Event*> Population::getBehavior(Universe* universe, Galaxy* galaxy)
{
	//printf("getBehavior\n");
	vector<Event*> events;

	// Event type set to move/1, PlanetID, GalaxyID
	int type = 1, pID, gID = 0;
	float time;

	int width = universe->getWidth();
	int length = universe->getLength();

	int x = galaxy->getGalaxyID()/width;
	int y = galaxy->getGalaxyID()%length;



	// Determine if this is a contested galaxy
	galaxyPopulationCounts summary = galaxy->getPopulationCounts();
	if(summary.flood != 0 && (summary.military != 0 || summary.civilian != 0))
	{	// Contested Galaxy
		gID = galaxy->getGalaxyID();

		if(flood != 0) { // Flood population: Attack.
			Population* newPop = new Population(0.75 * flood, 0, 0);
			flood *= 0.25;
			
			// Hit civilian targets first
			int planetCount = galaxy->getPlanetCount();
			if(summary.civilian != 0) {
				// Attack largest civilian population
				int maxCivPlanet = 0;
				int maxCivPop = 0;
				for(int i = 0; i < planetCount; i ++) {
					int civPop = galaxy->getPlanet(i)->getCivilianPopulation();
					if (civPop > maxCivPop) {
						maxCivPlanet = i;
						maxCivPop = civPop;
					}
				}
				pID = maxCivPlanet;
			} else {
				// Attack largest military population
				int maxMilPlanet = 0;
				int maxMilPop = 0;
				for(int i = 0; i < planetCount; i ++) {
					int milPop = galaxy->getPlanet(i)->getMilitaryPopulation();
					if (milPop > maxMilPop) {
						maxMilPlanet = i;
						maxMilPop = milPop;
					}
				}
				pID = maxMilPlanet;
			}
			//schedule move/attack event with newPop, gID, pID
			Event* newEvent = new Event(type, 0.0, pID, gID, newPop);
			events.push_back(newEvent);
		} else { // Human Population: Evacuate and Attack
			
			// Evacuating Civilians
			populationAnalysis* pop = getPopulationAnalysis(universe);
			// Getting best adjacent galaxy to send civilians to
			int destX = x;
			int destY = y;
			getCivilianEvacuationGalaxy(pop, &summary, &destX, &destY);
			// Check to make sure the best galaxy is not the current one
			if(destX != x && destY != y) {
				Population* newPop = new Population(0, civilian*0.75, 0);
				civilian *= 0.25;
				gID = destX*width + destY;
				pID = 0;
				// TODO: why 0 for pID? Schedule move/attack event with newPop, gID, pID
				Event* newEvent = new Event(type, 0.0, pID, gID, newPop);
				events.push_back(newEvent);
			}// Otherwise dont evacuate

			// Attacking Largest Flood population
			Population* newPop = new Population(0, 0, military*0.75);
			military *= 0.25;
			int planetCount = galaxy->getPlanetCount();
			int maxFloodPlanet = 0;
			int maxFloodPop = 0;
			for(int i = 0; i < planetCount; i ++) {
				int floodPop = galaxy->getPlanet(i)->getFloodPopulation();
				if (floodPop > maxFloodPop) {
					maxFloodPlanet = i;
					maxFloodPop = floodPop;
				}
			}
			pID = maxFloodPlanet;
			//Schedule move/attack event with newPop, gID, pID
			Event* newEvent = new Event(type, 0.0, pID, gID, newPop);
			events.push_back(newEvent);			

		}

	} else {
		// Uncontested Galaxy
		populationAnalysis* pop = getPopulationAnalysis(universe);
		if(flood != 0) { // Flood population: Attack.

		} else { // Human Population: Reinforce

		}
	}
	return events;
	
}

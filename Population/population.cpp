#include "population.h"
#include <stdio.h>
#include <stdlib.h>
#include <cilk/cilk.h>
#include <iostream>

Population::Population(int setFlood, int setCivilian, int setMilitary) {
	flood = setFlood;
	civilian = setCivilian;
	military = setMilitary;
}

// Takes in galactic coordinates and calls the lambda function on all valid neighbor galaxies
void Population::executeOnBorders(int x, int y, std::function<void (int, int)> func) {
	int mods[3] = {-1, 0, 1};
	for(int a = 0; a < 3; a ++) {
		for(int b = 0; b < 3; b ++) {
			int newX = x + mods[a];
			int newY = y + mods[b];
			// Filter out border conditions and center cell
			if (newX >= 0 && newY >= 0 && newX < LENGTH  && newY < WIDTH &&
			   (x != newX || y != newY)
			) {
				func(newX,newY);
			}
		}
	}
}

// Civilians run away from the flood. Writes back the coordinates of the safest adjacent galaxy.
void Population::getCivilianEvacuationGalaxy(populationAnalysis* pop, galaxyPopulationCounts* summary, int* x, int*y) {
	int destX = *x;
	int destY = *y;
	int minFlood = summary->flood;
	executeOnBorders(*x, *y, [&](int newX, int newY) {
		if(pop->flood[newX][newY] < minFlood) {
			minFlood = pop->flood[newX][newY];
			destX = newX;
			destY = newY;
		}
	});
	*x = destX;
	*y = destY;
	//std::cout << "CivilEvacGal" << destX << " " << destY << std::endl;
}

// Military chase the flood. Writes back the coordinates of the most infected adjacent galaxy.
void Population::getMilitaryAttackGalaxy(populationAnalysis* pop, galaxyPopulationCounts* summary, int* x, int*y) {
	int destX = *x;
	int destY = *y;
	int maxFlood = summary->flood;
	executeOnBorders(*x, *y, [&](int newX, int newY) {
		if(pop->flood[newX][newY] > maxFlood) {
			maxFlood = pop->flood[newX][newY];
			destX = newX;
			destY = newY;
		}
	});
	*x = destX;
	*y = destY;
	//std::cout << "MilAttackGal" << destX << " " << destY << std::endl;
}

// Flood chase civilians. Writes back the coordinates of the most civilian-populated adjacent galaxy.
void Population::getFloodAttackGalaxy(populationAnalysis* pop, galaxyPopulationCounts* summary, int* x, int*y) {
	int destX = *x;
	int destY = *y;
	int maxCiv = summary->civilian;
	executeOnBorders(*x, *y, [&](int newX, int newY) {
		if(pop->civilian[newX][newY] > maxCiv) {
			maxCiv = pop->civilian[newX][newY];
			destX = newX;
			destY = newY;
		}
	});
	*x = destX;
	*y = destY;
	//std::cout << "FloodAttackGal" << destX << " " << destY << std::endl;
}

// Civilians spread themselves roughly evenly over the planets in a sector.
int Population::getCivilianEvacuationPlanet(Galaxy* galaxy) {
	int planetCount = galaxy->getPlanetCount();
	int minCivPlanet = 0;
	int minCiv = galaxy->getPlanet(minCivPlanet)->getCivilianPopulation();
	// Get the planet with the smallest civilian population
	for(int i = 0; i < planetCount; i ++) {
		int currCiv = galaxy->getPlanet(i)->getCivilianPopulation();
		if(currCiv < minCiv) {
			minCiv = currCiv;
			minCivPlanet = i;
		}
	}
	return minCivPlanet;
}

// Military attack the most infected planet
int Population::getMilitaryAttackPlanet(Galaxy* galaxy) {
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
	return maxFloodPlanet;
}

// Flood attack the civilians first. Then the military.
int Population::getFloodAttackPlanet(Galaxy* galaxy) {
	int planetCount = galaxy->getPlanetCount();
	// Hit civilian targets first
	int civiliansInGalaxy = galaxy->getPopulationCounts().civilian;
	if(civiliansInGalaxy != 0) {
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
		return maxCivPlanet;
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
		return maxMilPlanet;
	}
}

// Uses a Q-Learning based technique to determine unit pathing between galaxies
populationAnalysis* Population::getPopulationAnalysis(Universe* universe) {
	//printf("getPopulationAnalysis\n");
	int width = WIDTH;
	int length = LENGTH;

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
	// do a number of times realative to the size of the universe
	for(int i = 0; i < width; i ++) {
		// For each x,y
		cilk_for(int x = 0; x < width; x ++) {
			for(int y = 0; y < length; y ++) {
				// Find the greatest value neighbor cell for each attribute
				int maxFlood = 0;
				int maxCiv = 0;
				executeOnBorders(x, y, [&](int newX, int newY) {
					if(pop->flood[newX][newY] > maxFlood) {
								maxFlood = pop->flood[newX][newY];
					}
					if(pop->civilian[newX][newY] > maxCiv) {
						maxCiv = pop->civilian[newX][newY];
					}
				});

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



// Uses populationAnalysis to determine the next action of the population in question
using std::vector;
vector<Event*> Population::getBehavior(Universe* universe, Galaxy* galaxy)
{
	//std::cout << "GetBehavior" << flood << " " << civilian << " " << military << std::endl;
	vector<Event*> events;

	// Event type set to move/1, PlanetID, GalaxyID
	int type = 0, pID, gID = 0;
	float time;

	int width = WIDTH; 
	int length = LENGTH;
	int galaxyID = galaxy->getGalaxyID();
	int x = galaxy->getGalaxyID()/width;
	int y = galaxy->getGalaxyID()%length;

	// Determine if this is a contested galaxy
	galaxyPopulationCounts summary = galaxy->getPopulationCounts();
	if(summary.flood != 0 && (summary.military != 0 || summary.civilian != 0)) {
		//**********Contested Galaxy**********//
		gID = galaxy->getGalaxyID();

		if(flood != 0) { 
			//-----Flood population: Attack.-----//
			Population* newPop = new Population(0.75 * flood, 0, 0);
			flood *= 0.25;
			pID = getFloodAttackPlanet(galaxy);
			//schedule move/attack event with newPop, gID, pID
			Event* newEvent = new Event(type, 0.0, pID, gID, newPop);
			events.push_back(newEvent);
		} else { 
			//-----Human Population: Evacuate and Attack-----//
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
				pID = getCivilianEvacuationPlanet(universe->getGalaxy(destX, destY));
				Event* newEvent = new Event(type, 0.0, pID, gID, newPop);
				events.push_back(newEvent);
			}// Otherwise dont evacuate

			// Military attacking Largest Flood population
			Population* newPop = new Population(0, 0, military*0.75);
			military *= 0.25;
			pID = getMilitaryAttackPlanet(galaxy);
			//Schedule move/attack event with newPop, gID, pID
			Event* newEvent = new Event(type, 0.0, pID, gID, newPop);
			events.push_back(newEvent);			

		}

	} else {
		//**********Uncontested Galaxy**********//
		populationAnalysis* pop = getPopulationAnalysis(universe);
		if(flood != 0) { 
			//-----Flood population: Reinforce-----//
			int destX = x;
			int destY = y;
			getFloodAttackGalaxy(pop, &summary, &destX, &destY);
			Population* newPop = new Population(flood*0.75, 0, 0);
			flood /= 4;
			gID = destX*width + destY;
			pID = getFloodAttackPlanet(universe->getGalaxy(destX, destY));
			Event* newEvent = new Event(type, 0.0, pID, gID, newPop);
			events.push_back(newEvent);
		} else { 
			//-----Human population: Spread out Civilians and Attack-----//
			// Spreading out Civilians
			pID = getCivilianEvacuationPlanet(galaxy);
			// Only make the move if the other planet's population is much smaller
			if(galaxy->getPlanet(pID)->getCivilianPopulation() < civilian/4) {
				Population* newPop = new Population(0, civilian/2, 0);
				civilian /= 2;
				pID = getCivilianEvacuationPlanet(galaxy);
				Event* newEvent = new Event(type, 0.0, pID, gID, newPop);
				events.push_back(newEvent);	
			}

			// Attacking Flood
			int destX = x;
			int destY = y;
			getMilitaryAttackGalaxy(pop, &summary, &destX, &destY);
			Population* newPop = new Population(0, 0, military*0.75);
			military /= 4;
			gID = destX*width + destY;
			pID = getMilitaryAttackPlanet(universe->getGalaxy(destX, destY));
			Event* newEvent = new Event(type, 0.0, pID, gID, newPop);
			events.push_back(newEvent);
		}
	}
	return events;
	
}

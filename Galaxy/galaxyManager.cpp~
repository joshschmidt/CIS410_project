#include "galaxyManager.h"
#include <stdio.h>      
#include <stdlib.h>     
#include <time.h> 
#include <cilk/cilk.h>




GalaxyManager::GalaxyManager(Galaxy * g, Universe * u) {
	galaxy = g;
	universe = u;
	sim_time = 0.0;
	min_time_next_event = 1.0e+29;
	next_event_type = -1;
}

populationAnalysis* GalaxyManager::getPopulationAnalysis() {
	// Find initial values
	populationAnalysis* pop = new populationAnalysis;
	cilk_for(int i = 0; i < 1000; i ++) {
		for(int j = 0; j < 1000; j ++) {
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
		cilk_for(int x = 0; x < 1000; x ++) {
			for(int y = 0; y < 1000; y ++) {
				// Find the greatest value neighbor cell for each attribute
				int maxFlood = 0;
				int maxCiv = 0;
				int mods[3] = {-1, 0, 1};
				for(int a = 0; a < 3; a ++) {
					for(int b = 0; b < 3; b ++) {
						int newX = x + mods[a];
						int newY = y + mods[b];
						// Filter out border conditions and center cell
						if (newX < 0 && newY < 0 && newX < 1000 && newY < 1000 &&
						   (x != newX || y != newY)
						) {
							if(pop->flood[newX][newY] > maxFlood) {
								maxFlood = pop->flood[newX][newY];
							}
							if(pop->civilian[newX][newY] > maxCiv) {
								maxCiv = pop->civilian[newX][newY];
							}
						}
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

void GalaxyManager::addEvent(Event e) {
	pq.push(e);
}


void GalaxyManager::handleEvent(Event e) {

	switch(e.getType()) {

		case 0:
			battle(e.getpID());
			break;
			



	}

}

void GalaxyManager::battle(int pID) {
	Planet * p = galaxy->getPlanet(pID);
 
	float weather = p->getWeather() * 2;
	float terrain = p->getTerrain() * 2;
	float gravity = p->getGravity() * 2;

	Population * pop = p->getPopulation();

	int flood = pop->getFlood();
	int civ = pop->getCiv();
	int mil = pop->getMilitary();

	int humanPower, floodPower = 0;

	

	humanPower = mil + (.25 * civ) + (10 * weather) + (10 * terrain) + (10 * gravity);
	floodPower = flood + (10 / weather) + (10 / terrain) + (10 / gravity);


	if(humanPower > floodPower) {
		int diff = humanPower - floodPower;
		if(flood - diff < 0) {
			flood = 0;
			mil = mil * static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
		}

		else {
			flood = flood - diff;
			mil = mil * .75;
		}		

	}

	else {
		int diff = floodPower - humanPower;
		if(mil - diff < 0) {
			mil = 0;
			flood = flood * static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
			flood += civ * .75;
			civ = 0;
		}

		else {
			mil = mil - diff;
			flood = flood * .75;
	
		}
	}

	pop->setMilitary(mil);
	pop->setFlood(flood);
	pop->setCiv(civ);
}




void GalaxyManager::timing() {

	Event nextEvent = pq.top();
	min_time_next_event = nextEvent.getTime();
	next_event_type = nextEvent.getType();
	sim_time = min_time_next_event;
	handleEvent(nextEvent);
	pq.pop();

}

void GalaxyManager::advanceSim(int time) {

	while(sim_time < time) {

		timing();		
	

	}






}

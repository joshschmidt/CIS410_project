#include "galaxyManager.h"
#include <stdio.h>      
#include <stdlib.h>     
#include <time.h> 



GalaxyManager::GalaxyManager(Galaxy * g) {
	galaxy = g;
	sim_time = 0.0;
	min_time_next_event = 1.0e+29;
	next_event_type = -1;
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

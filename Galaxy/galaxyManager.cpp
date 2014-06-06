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

void GalaxyManager::init() {

	for(int i = 0; i < galaxy->getPlanetCount(); i++) {
		addEvents(galaxy->getPlanet(i)->getPopulation()->getBehavior(universe, galaxy));	
	}
}


void GalaxyManager::addEvents(std::vector<Event*> eventList) {
	for(Event * event : eventList) {
		event->setTime(sim_time + (static_cast <float> (rand()) / static_cast <float> (RAND_MAX) * 10));
		event->printEvent();
		std::cout << galaxy->getGalaxyID() << "'s Queue Size: " << pq.size() << "\n";
		pq.push(*event);
	}
}


void GalaxyManager::handleEvent(Event e) {

	switch(e.getType()) {

		case 0:
			battle(e.getpID());
			printf("battle happening \n");
			e.printEvent();
			break;
		case 1:
			moveInterplanet(e.getPopulation(), e.getgID(), e.getpID());
			printf("move happening \n");
			e.printEvent();
			break;
	}

}

void GalaxyManager::moveInterplanet(Population * newPop, int gID, int pID){
	//get the galaxy
	Galaxy g = universe->getGalaxy(gID);

	//get the planet with the gicen galaxy
	Planet * p = g.getPlanet(pID);

	//set the planet's population to be the sum of it's current population and the new population
	p->getPopulation()->setMilitary(p->getPopulation()->getMilitary()+newPop->getMilitary());
	p->getPopulation()->setFlood(p->getPopulation()->getFlood()+newPop->getFlood());
	p->getPopulation()->setCiv(p->getPopulation()->getCiv()+newPop->getCiv());

	//generate the next event(s)
	addEvents(p->getPopulation()->getBehavior(universe, galaxy));
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

	//generate the next event(s)
	addEvents(pop->getBehavior(universe, galaxy));
}

void GalaxyManager::timing() {
	//retrive the next event from the queue
	std::cout << "2Queue size after initiliazation: " << pq.size() << "\n";
	Event nextEvent = pq.top();
	//fetch the "duration" of the next event
	min_time_next_event = nextEvent.getTime();
	//fetch the type of event
	next_event_type = nextEvent.getType();
	//advance the sim clock
	sim_time = min_time_next_event;
	//process the event, the next event will be generated at the end
	handleEvent(nextEvent);
	//remove the processed event from the queue
	pq.pop();
	//deallocate memory used by event.
	//delete &nextEvent;

}

void GalaxyManager::advanceSim(int time) {
	
	//keep running the simulation as long as there's time left
	while(sim_time < time) {
		std::cout << "1Queue size after initiliazation: " << pq.size() << "\n";
		//invoke the timing manager
		timing();		
	

	}






}

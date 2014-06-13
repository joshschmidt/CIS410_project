#include "galaxyManager.h"
#include <stdio.h>      
#include <stdlib.h>     
#include <time.h> 
#include <cilk/cilk.h>




GalaxyManager::GalaxyManager(UniverseManager* um, Galaxy * g, Universe * u) {
	universeManager = um;
	galaxy = g;
	universe = u;
	sim_time = 0.0;
	min_time_next_event = 1.0e+29;
	next_event_type = -1;
	pq = new std::priority_queue<Event*, std::vector<Event*>, CompareEvent>();
	
}

void GalaxyManager::init() {
	std::vector<Event*> eq = std::vector<Event*>();
	int gID = galaxy->getGalaxyID();
	for(int i = 0; i < galaxy->getPlanetCount(); i++) {
		Event * e = new Event(EVAL,1.0,i,gID,NULL);
		eq.push_back(e);	
	}
	addEvents(eq);
	
}

void GalaxyManager::printGalaxy() {
	std::cout << "Galaxy: " << galaxy->getID() << " Queue Size: " << pq->size() << "\n";
}


void GalaxyManager::addEvents(std::vector<Event*> eventList) {
	for(Event * event : eventList) {
		event->setTime(sim_time + (static_cast <float> (rand()) / static_cast <float> (RAND_MAX) * 10));
		//event->printEvent();
		//std::cout << galaxy->getGalaxyID() << "'s Queue Size: " << pq->size() << "\n";

		// Determine whether the event is local to this galaxy or should be sent to another one
		if(event->getgID() == galaxy->getGalaxyID()) {
			pq->push(event);
			std::cout << "Local Event\n";
		} else {
			std::cout << "Redirecting Event\n";
			universeManager->redirectEvent(event->getgID(), event);
		}
		//std::cout << pq << "\n"; 

	}
}

void GalaxyManager::addExtragalacticEvent(Event* newEvent) {
	extraGalacticEvents.push_back(newEvent);
}

void GalaxyManager::handleEvent(Event * e) {
	//printGalaxy();

	switch(e->getType()) {

		case 0:
			// Forces arrive on a planet and a battle happens
			moveInterplanet(e->getPopulation(), e->getgID(), e->getpID());
			battle(e->getpID());

			//printf("battle happening \n");
			//e->printEvent();
			break;
		case 1:
			// Re-Evaluate behavior at this time
			addEvents(galaxy->getPlanet(e->getpID())->getPopulation()->getBehavior(universe, galaxy));
			//printf("evaluation happening \n");
			//e->printEvent();
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
	//addEvents(p->getPopulation()->getBehavior(universe, galaxy));
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

	// Humans Win
	if(humanPower > floodPower) {
		flood = 0;
		mil = mil * static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
		std::cout << "Human Victory\n";

	}
	// Flood Wins
	else {
		mil = 0;
		flood = flood * static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
		flood += civ * .75;
		civ = 0;
		std::cout << "Flood Victory\n";
	}

	pop->setMilitary(mil);
	pop->setFlood(flood);
	pop->setCiv(civ);

	//addEvents(pop->getBehavior(universe, galaxy));
	// Instead, Set the next event from this unit to be scheduled some time later
	std::vector<Event*> events;
	Event* newEvent = new Event(EVAL, (sim_time+10), pID, galaxy->getID(), pop);
	events.push_back(newEvent);
	addEvents(events);
}

void GalaxyManager::timing() {
	if(pq->size() == 0) return;
	//printf("PQ SIZE %d\n", (int)pq->size());
	//retrive the next event from the queue
	Event * nextEvent = pq->top();
	//fetch the "duration" of the next event
	min_time_next_event = nextEvent->getTime();
	//fetch the type of event
	next_event_type = nextEvent->getType();
	//advance the sim clock
	sim_time = min_time_next_event;
	//process the event, the next event will be generated at the end
	handleEvent(nextEvent);
	//remove the processed event from the queue
	Event* killMe = pq->top();
	pq->pop();
	//delete killMe->getPopulation();
	//delete killMe;
	//deallocate memory used by event.
	//delete &nextEvent;

}

void GalaxyManager::advanceSim(int time) {
	//keep running the simulation as long as there's time left

	while(sim_time < time && pq->size() !=0) {
		// Handle extragalactic events
		int size = extraGalacticEvents.size();
		for(int i = 0; i < size; i ++) {
			pq->push(extraGalacticEvents.front());
			extraGalacticEvents.erase(extraGalacticEvents.begin());
		}
		//invoke the timing manager
		timing();
	}
}

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




	}

}

void GalaxyManager::battle(int pID) {
	Planet p = galaxy->getPlanet(pID); 
	float w = p.getWeather();
	float t = p.getTerrain();
	float g = p.getGravity();

}


void GalaxyManager::timing() {

	Event nextEvent = pq.top();
	min_time_next_event = nextEvent.getTime();
	next_event_type = nextEvent.getType();
	sim_time = min_time_next_event;
	pq.pop();

}

void GalaxyManager::advanceSim(int time) {


}

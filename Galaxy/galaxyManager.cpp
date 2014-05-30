#include "galaxyManager.h"    
#include <stdio.h>      
#include <stdlib.h>     
#include <time.h> 



GalaxyManager::GalaxyManager(Galaxy * g) {
	galaxy = g;
}

void GalaxyManager::addEvent(Event e) {
	pq.push(e);
}

Event GalaxyManager::nextEvent() {
	return pq.top();
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

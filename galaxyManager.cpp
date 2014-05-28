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

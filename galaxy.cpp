#include "galaxy.h"    
#include <stdio.h>      
#include <stdlib.h>     
#include <time.h> 

Galaxy::Galaxy(int seed, int id, int planetCount) {
	_id = id;
	for(int i = 0; i < planetCount; i++) {
		_planets[i] = new Planet(seed, i, _id);
		_planets[i]->printPlanet();
		
	}
}

Planet Galaxy::getPlanet(int planetId){
	return *_planets[planetId];
}

void Galaxy::printGalaxy() {
	printf("(Galaxy Id: %d)", _id);
}




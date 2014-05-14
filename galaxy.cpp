#include "galaxy.h"    
#include <stdio.h>      
#include <stdlib.h>     
#include <time.h> 

Galaxy::Galaxy(int seed, int id, int planetCount) {
	for(int i = 0; i < planetCount; i++) {
		_planets[i] = Planet(seed, i);
	}
}

Planet Galaxy::getPlanet(int planetId){
	return _planets[planetId];
}

void Galaxy::printGalaxy() {
	printf("WOAH");
}




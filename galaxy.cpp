#include "galaxy.h"    
#include <stdio.h>      
#include <stdlib.h>     
#include <time.h>
#include <math.h> 

Galaxy::Galaxy(int seed, int id, int planetCount) {
	_id = id;
	_planets = new Planet*[planetCount];
	for(int i = 0; i < planetCount; i++) {
		_planets[i] = new Planet(seed, i, _id);
		//_planets[i]->printPlanet();
		
	}
}

Planet Galaxy::getPlanet(int planetId){
	return *_planets[planetId];
}

double Galaxy::getDistance(int id1, int id2) {
	Planet * p1 = _planets[id1];
	Planet * p2 = _planets[id2];
	
	int xd = p1->getX() - p2->getX();
	int yd = p1->getY() - p2->getY();
	int zd = p1->getZ() - p2->getZ();

	return sqrt(float(xd*xd + yd*yd + zd*zd));	
}


void Galaxy::printGalaxy() {
	printf("(Galaxy Id: %d)", _id);
}




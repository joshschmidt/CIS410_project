#include "galaxy.h"    
#include <stdio.h>      
#include <stdlib.h>     
#include <time.h>
#include <math.h> 
#include <cilk/cilk.h>

Galaxy::Galaxy(int seed, int id, int planetCount) {
	_id = id;
	_planetCount = planetCount;
	_planets = new Planet*[planetCount];
	for(int i = 0; i < planetCount; i++) {
		_planets[i] = new Planet(seed, i, _id);
		//_planets[i]->printPlanet();
		
	}
}

Planet * Galaxy::getPlanet(int planetId){
	return _planets[planetId];
}

void debug()
{


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

//return a struct that contains the population counts off all the planets in the galaxy
galaxyPopulationCounts Galaxy::getPopulationCounts(){
	//declare the struct
	galaxyPopulationCounts currentPopulation;
	currentPopulation.flood = 0;
	currentPopulation.civilian = 0;
	currentPopulation.military = 0;
	//itterate through each planet and sum up the populations, storing in the struct currentPopulation
	for(int i = 0; i < _planetCount; i++){
		currentPopulation.flood += _planets[i]->getFloodPopulation();
		currentPopulation.civilian += _planets[i]->getCivilianPopulation();
		currentPopulation.military += _planets[i]->getMilitaryPopulation();
	}
	if(currentPopulation.flood < 0 || currentPopulation.flood > 1000)
	{
		debug();
	}
	//return the struct
	return currentPopulation;
}




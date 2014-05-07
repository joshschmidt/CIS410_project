#include "planet.h"
#include <stdio.h>      
#include <stdlib.h>     
#include <time.h>       

float getRand() {
	return static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
}


Planet::Planet(int seed) {
	srand (seed);
	//population constructor
	size = getRand();
	terrain = getRand();
	weather = getRand();
	gravity = getRand();

}


float Planet::getTerrain() {
	return terrain;
}

float Planet::getWeather() {
	return weather;
}

float Planet::getGravity() {
	return gravity;
}

void Planet::printPlanet() {
	printf("Size: %f \nTerrain: %f \nWeather: %f \nGravity: %f \n", size, terrain, weather, gravity);
}




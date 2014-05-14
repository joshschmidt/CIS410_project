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
	terrain = getRand();
	weather = getRand();
	gravity = getRand();
	x = (rand()%(1000));
	y = (rand()%(1000));
	z = (rand()%(1000));
}


float Planet::getTerrain() { return terrain; }
float Planet::getWeather() { return weather; }
float Planet::getGravity() { return gravity; }
int Planet::getX() { return x; }
int Planet::getY() { return y; }
int Planet::getZ() { return z; }


void Planet::printPlanet() {
	printf("Location: (%d, %d, %d) \nTerrain: %f \nWeather: %f \nGravity: %f \n\n", x, y, z, terrain, weather, gravity);
}

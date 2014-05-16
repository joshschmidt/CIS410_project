#include "planet.h"    
#include <stdio.h>      
#include <stdlib.h>     
#include <time.h> 

float getRand() {
	return static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
}


Planet::Planet(int seed, int id, int galaxyId) {
	//srand (seed);
	//population constructor
	_id = id;
	_galaxyId = galaxyId;
	_terrain = getRand();
	_weather = getRand();
	_gravity = getRand();
	_x = (rand()%(1000));
	_y = (rand()%(1000));
	_z = (rand()%(1000));
}


float Planet::getTerrain() { return _terrain; }
float Planet::getWeather() { return _weather; }
float Planet::getGravity() { return _gravity; }
int Planet::getX() { return _x; }
int Planet::getY() { return _y; }
int Planet::getZ() { return _z; }


void Planet::printPlanet() {
	printf("(Planet Id: %d)(Galaxy Id: %d)\n", _id, _galaxyId);
	printf("Location: (%d, %d, %d) \nTerrain: %f \nWeather: %f \nGravity: %f \n\n", _x, _y, _z, _terrain, _weather, _gravity);
}

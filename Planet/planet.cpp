#include "planet.h"    
#include <stdio.h>      
#include <stdlib.h>     
#include <time.h> 

#define P_SIZE 1000

float getRand() {
	return static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
}


Planet::Planet(int seed, int id, int galaxyId) {
	//srand (seed);
	//population constructor
	int c, m, f = 0;

	if(rand()%10 == 0) {
		f = (rand()%(P_SIZE));
		c = 0;
		m = 0;
	}

	else {
		f = 0;
		c = (rand()%(P_SIZE));
		m = (rand()%(P_SIZE/10));	
	}
	printf("(%d, %d, %d)\n", f, c, m );
	population = new Population(f,c,m);
	_id = id;
	_galaxyId = galaxyId;
	_terrain = getRand();
	_weather = getRand();
	_gravity = getRand();
	_x = (rand()%(1000));
	_y = (rand()%(1000));
	_z = (rand()%(1000));
}

//return a planet's stats and location
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

//return the planet's population object
Population * Planet::getPopulation() { return population; }

//return the planet's flood population
int Planet::getFloodPopulation() { return population->getFlood(); }

//return the planet's civilian population
int Planet::getCivilianPopulation() { return population->getCiv(); }

//return the planet's military population
int Planet::getMilitaryPopulation() { return population->getMilitary(); }



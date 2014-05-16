#include "universe.h"    
#include <stdio.h>      
#include <stdlib.h>     
#include <time.h> 
Universe::Universe(int seed, int id, int length, int width, int height) {
	_id = id;
	_length = length;
	_width = width;
	_height = height;
	_galaxies = new (Galaxy**)[length]; 

	// Create 2D array of pointers:
	_galaxies = new (Galaxy**)[length];
	for (int i = 0; i < length; ++i) {
  		_galaxies[i] = new (Galaxy**)[width];
	}

	for(int x = 0; x < length; x++) {
		for(int z = 0; z < width; z++) {
			printf("(x:%d, z:%d)", x, z);
			_galaxies[x][z] = new Galaxy(seed, (x * length) + z, 5);
			_galaxies[x][z]->printGalaxy();
		}
	}
}

Galaxy Universe::getGalaxy(int galaxyId) {
	int x = galaxyId % _length;
	int z = galaxyId / _width;
	return *_galaxies[x][z];
}

//alternate universes!?
void Universe::printUniverse() {
	printf("Number of Universes: 1");
}



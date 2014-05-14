#include "universe.h"    
#include <stdio.h>      
#include <stdlib.h>     
#include <time.h> 
Universe::Universe(int seed, int id, int length, int width, int height) {
	_id = id;
	_length = length;
	_width = width;
	_height = height;

	for(int x = 0; x < length; x++) {
		for(int z = 0; z < width; z++) {
			_galaxies[x][z] = Galaxy(seed, x * z, 1000);
		}
	}
}

Galaxy Universe::getGalaxy(int galaxyId) {
	int x = galaxyId % _length;
	int z = galaxyId / _width;
	return _galaxies[x][z];
}

//alternate universes!?
void Universe::printUniverse() {
	printf("Number of Universes: 1");
}




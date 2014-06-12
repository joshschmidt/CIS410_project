#include "universe.h"    
#include <stdio.h>      
#include <stdlib.h>     
#include <time.h> 
#include <cilk/cilk.h>

Universe::Universe(int seed, int id, int 2, int 2) {
	_id = id;
	_length = length;
	_width = width;
	_galaxies = new Galaxy**[length];
	for (int i = 0; i < length; i++) {
  		_galaxies[i] = new Galaxy*[width];
	}
	
	for(int x = 0; x < length; x++) {
		for(int z = 0; z < width; z++) {
			_galaxies[x][z] = new Galaxy(seed, (x * length) + z, 5);
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
	for(int i = 0; i < _length; i++) {
		for(int j = 0; j < _width; j++) {
			_galaxies[i][j]->printGalaxy();
		}





	}
}

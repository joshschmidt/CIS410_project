#include "universe.h"    

Universe::Universe(int seed, int id, int length, int width, int height) {
	for(int x = 0; x < length; x++) {
		for(int z = 0; z < width; z++) {
			galaxies[x][y] = Galaxy(seed, x * z, 1000);
		}
	}
}


//alternate universes!?
void Universe::printUniverse() {
	printf("Number of Universes: 1");
}




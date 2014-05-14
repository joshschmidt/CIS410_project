#include "galaxy.h"    


Galaxy::Galaxy(int seed, int planetCount) {
	cilk_for(int i = 0; i < planetCount; i++) {
			planets[i] = Planet(seed, i);
		}
	}
}


void Galaxy::printGalaxy() {
	printf("WOAH");
}




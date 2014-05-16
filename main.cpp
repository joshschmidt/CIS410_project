#include "universe.h"
#include <stdio.h>      
#include <stdlib.h> 
#include <cilk/cilk.h>


int main() {
	Universe universe = Universe(1, 1, 5, 5, 5);
	universe.getGalaxy(0).getPlanet(0).printPlanet();
}

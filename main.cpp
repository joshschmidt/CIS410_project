#include "universe.h"
#include <stdio.h>      
#include <stdlib.h> 
#include <cilk/cilk.h>


int main() {
	Universe universe = Universe(1, 1);
	universe.galaxies[1][1].planets[1].printPlanet();
}

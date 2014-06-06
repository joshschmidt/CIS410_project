#include "Universe/universe.h"
#include "Universe/universeManager.h"
#include "Event/event.h"
#include <stdio.h>      
#include <stdlib.h> 
#include <iostream>
//#include "../sdl/include/SDL2/SDL.h"



int main() {

	Universe universe = Universe(1, 1, 1, 1);
	//universe.printUniverse();
	UniverseManager universeManager = UniverseManager(&universe);
	universeManager.runSim();

	

	return 0;
}

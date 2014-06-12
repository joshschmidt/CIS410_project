#include "Universe/universe.h"
#include "Universe/universeManager.h"
#include "Event/event.h"
#include <stdio.h>      
#include <stdlib.h> 
#include <iostream>

int main() {
	Universe universe = Universe(2, 1, LENGTH, WIDTH);
	UniverseManager universeManager = UniverseManager(&universe);
	universeManager.runSim();
	return 0;
}

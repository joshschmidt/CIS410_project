#include "Universe/universe.h"
#include "Universe/universeManager.h"
#include "Event/event.h"
#include <stdio.h>      
#include <stdlib.h> 
#include <iostream>

int main() {
	Universe universe = Universe(1, 1, 2, 2);
	UniverseManager universeManager = UniverseManager(&universe);
	universeManager.runSim();
	return 0;
}

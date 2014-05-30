#include "Universe/universe.h"
#include "Galaxy/galaxyManager.h"
#include "Event/event.h"
#include <stdio.h>      
#include <stdlib.h> 
#include <iostream>



int main() {
	Galaxy g = Galaxy(1,1,1);
	GalaxyManager gm = GalaxyManager(&g);
	Event e = Event(1,1,1,1);
	gm.addEvent(e);
	Universe universe = Universe(1, 1, 1000, 1000, 1000);
}

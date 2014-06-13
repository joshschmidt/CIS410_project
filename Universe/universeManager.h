#ifndef UNIVERSEMANAGER_H
#define UNIVERSEMANAGER_H
#include "../Event/event.h"
#include "../Universe/universe.h"
#include "../Galaxy/galaxyManager.h"
#include "../Population/population.h"
#include <iostream>
#include <queue>
#include <iomanip>
#include <vector>
#include <cilk/cilk.h>
#include "../structs.h"

class GalaxyManager;
     
class UniverseManager{
	private:
		Universe * universe;
                //list of galaxy managers
                std::vector<GalaxyManager*> * managers;
	     
	public:
		UniverseManager(Universe * u);
		void redirectEvent(int gID, Event* event);
		void printUniverse();
		void runSim();
		void InitSDL();
		void Render();
                      
     
};
#endif



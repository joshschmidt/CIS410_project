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
     
class UniverseManager{
	private:
		Universe * universe;
                //list of galaxy managers
                std::vector<GalaxyManager> managers;
	     
	public:
		UniverseManager(Universe * u);
		void advanceSim();
		void Init();
		void Render();
                      
     
};
#endif



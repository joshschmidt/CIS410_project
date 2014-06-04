#include "universeManager.h"    
#include <stdio.h>      
#include <stdlib.h>    
#include <time.h>
     
     
     
UniverseManager::UniverseManager(Universe * u) {
	universe = u;
        int length = universe->getLength();
        int width = universe->getWidth();
        for(int i = 0; i < length; i++) {
	        for(int j = 0; j < width; j++) {
	                managers.push_back(GalaxyManager(u->getGalaxy(i,j), universe));                
                    }
     
            }
             
    }
     
void UniverseManager::advanceSim() {
     
    //here is where the thread delegation goes to the individual galaxy managers
     
     
}



#ifndef GALAXYMANAGER_H
#define GALAXYMANAGER_H
#include "../Event/event.h"
#include "../Galaxy/galaxy.h"
#include "../Population/population.h"
#include "../Universe/universe.h"
#include "../Universe/universeManager.h"
#include "../structs.h"
#include <iostream>
#include <queue>
#include <iomanip>
#include <vector>


class UniverseManager;

class CompareEvent {
    public:
    bool operator()(Event * e1, Event * e2) // Returns true if e1 is earlier than e2
    {
       if (e1->getTime() < e2->getTime()) return true;
       return false;
    }
};

class GalaxyManager
{
	private:
		UniverseManager* universeManager;
		Galaxy * galaxy;
		Universe * universe;
		float sim_time;
		float min_time_next_event;
		int next_event_type;
		
		 
		std::priority_queue<Event*, std::vector<Event *>, CompareEvent> * pq;
		std::vector<Event*> extraGalacticEvents;
	     

	public:
		GalaxyManager(UniverseManager* um, Galaxy * g, Universe * u);

		void addEvents(std::vector<Event*> eventList);
		void addExtragalacticEvent(Event* newEvent);
		void handleEvent(Event * e);
		void battle(int pID);
		//takes a population object, galaxy ID and planet ID and then adds the population from newPop
		//onto the planet's pop.
		void moveInterplanet(Population * newPop, int gID, int pID);
		void moveIntergalactic();
		void timing();
		void advanceSim(int time);
		void init();
		void printGalaxy();

		

};

#endif

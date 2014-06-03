#ifndef GALAXYMANAGER_H
#define GALAXYMANAGER_H
#include "../Event/event.h"
#include "../Galaxy/galaxy.h"
#include "../Population/population.h"
#include <iostream>
#include <queue>
#include <iomanip>
#include <vector>


class CompareEvent {
    public:
    bool operator()(Event& e1, Event& e2) // Returns true if e1 is earlier than e2
    {
       if (e1.getTime() < e2.getTime()) return true;
       return false;
    }
};

class GalaxyManager
{
	private:
		Galaxy * galaxy;
		Event next_event;
		float sim_time;
		float min_time_next_event;
		int next_event_type;
		
		 
		std::priority_queue<Event, std::vector<Event>, CompareEvent> pq;
	     

	public:
		GalaxyManager(Galaxy * g);
		void addEvent(Event e);
		void handleEvent(Event e);
		void battle(int pID);
		void timing();
		void advanceSim(int time);

		

};

#endif

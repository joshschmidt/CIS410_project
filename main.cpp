#include "universe.h"
#include <stdio.h>      
#include <stdlib.h> 
#include <iostream>
#include <queue>

struct Event {
	float time;
}

class TimeCompare {
	public:
		bool operator()(Event& e1, Event& e2) {
			if (e1.time < e2.time) return true;
			return false;
		}

};


int main() {
	Universe universe = Universe(1, 1, 5, 5, 5);
	priority_queue<Event, vector<Event>, TimeCompare> pq
}

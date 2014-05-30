#include "event.h"    
#include <stdio.h>      
#include <stdlib.h>     
#include <time.h> 



Event::Event(int type, float time, int pID, int gID) {
	_type = type;
	_time = time;
	_planetID = pID;
	_galaxyID = gID;
}

void Event::printEvent() {
	printf("Event: %d %f %d %d", _type, _time, _planetID, _galaxyID);
}

float Event::getTime() {
	return _time;
}

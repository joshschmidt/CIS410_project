#ifndef EVENT_H
#define EVENT_H

#define ATTACK 0
#define EVAL 1

#include "../Population/population.h"

class Population;

class Event
{
	private:
		int _type;
		float _time;
		int _planetID;
		int _galaxyID;
		Population* _population;
	     

	public:
		Event(int type, float time, int pID, int gID, Population* population);
		void printEvent();
		int getpID(){return _planetID;};
		int getgID(){return _galaxyID;};
		int getType(){return _type;};
		float getTime(){return _time;};
		void setTime(float t){_time = t;};
		Population* getPopulation() {return _population;};


};

#endif

#ifndef QUEUE_H
#define QUEUE_H

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


class Queue
{
	private:
		int _numEvents;
		//priority_queue<Event, vector<Event>, TimeCompare> pq
	public:
		Queue();
		


#ifndef UNIVERSE_H
#define UNIVERSE_H
#include "galaxy.h"


class Universe
{

	private:
		int id;
		Galaxy galaxies[][]; 

	public:
		Universe(int seed, int id);
		Galaxy getGalaxy(int galaxyId);
		void printUniverse();

};

#endif

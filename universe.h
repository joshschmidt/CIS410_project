#ifndef UNIVERSE_H
#define UNIVERSE_H
#include "galaxy.h"
#include <stdio.h>      
#include <stdlib.h>     
#include <time.h>   

class Universe
{

	private:
		int id;
		Galaxy ** galaxies; 

	public:
		Universe(int seed, int id, int length, int width, int height);
		Galaxy getGalaxy(int galaxyId);
		void printUniverse();

};

#endif

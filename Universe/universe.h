#ifndef UNIVERSE_H
#define UNIVERSE_H
#include "../Galaxy/galaxy.h"

  

class Universe
{

	private:
		int _id;
		int _length;
		int _width;
		Galaxy *** _galaxies; 

	public:
		Universe(int seed, int id, int length, int width);
		Galaxy getGalaxy(int galaxyId);
		void printUniverse();

};

#endif

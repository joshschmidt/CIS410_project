#ifndef UNIVERSE_H
#define UNIVERSE_H
#include "Galaxy/galaxy.h"

  

class Universe
{

	private:
		int _id;
		int _length;
		int _width;
		int _height;
		Galaxy *** _galaxies; 

	public:
		Universe(int seed, int id, int length, int width, int height);
		Galaxy getGalaxy(int galaxyId);
		void printUniverse();

};

#endif

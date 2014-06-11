#ifndef UNIVERSE_H
#define UNIVERSE_H

#include "../Galaxy/galaxy.h"

#define LENGTH 1
#define WIDTH 1

class Planet;
class Galaxy;
class Population;

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
		Galaxy* getGalaxy(int x, int y){return _galaxies[x][y];};
		void printUniverse();
		void drawUniverse();
		int getLength(){return _length;};
		int getWidth(){return _width;};
		

};

#endif

#ifndef UNIVERSE_H
#define UNIVERSE_H
#include "../Galaxy/galaxy.h"

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
		Galaxy * getGalaxy(int w, int l){return _galaxies[w][l];};
		void printUniverse();
		void drawUniverse();
		int getLength(){return _length;};
		int getWidth(){return _width;};
		

};

#endif

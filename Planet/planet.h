#ifndef PLANET_H
#define PLANET_H

#include "../Population/population.h"



class Planet
{
	private:
		int _id;
		Population * population;
		int _galaxyId;
		float _terrain;
		float _weather;
		float _gravity;
		int _x;
		int _y;
		int _z;
		//Population, object that describes behavior/preferences of planet's inhabitants 
		//Entities[]; need containers for different types of units
	     

	public:
		Planet(int seed, int id, int galaxyId);
		float getTerrain();
		float getWeather();
		float getGravity();
		int getX();
		int getY();
		int getZ();
		void printPlanet();
		Population * getPopulation();
		//get population attributes

};

#endif

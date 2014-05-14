#ifndef PLANET_H
#define PLANET_H



class Planet
{
	private:
		int id;
		float terrain;
		float weather;
		float gravity;
		int x;
		int y;
		int z;
		//Population, object that describes behavior/preferences of planet's inhabitants 
		//Entities[]; need containers for different types of units
	     

	public:
		Planet(int seed, int id);
		float getTerrain();
		float getWeather();
		float getGravity();
		int getX();
		int getY();
		int getZ();
		void printPlanet();
		//get population attributes

};

#endif

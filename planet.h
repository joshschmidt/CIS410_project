#ifndef PLANET_H
#define PLANET_H



class Planet
{
private:
    //Population, object that describes behavior/preferences of planet's inhabitants 
    //Entities[]; need containers for different types of units
    float terrain;
    float weather;
    float gravity;
    int x;
    int y;
    int z;
     

    


 
public:
    Planet(int seed);
    //get population attributes
    float getTerrain();
    float getWeather();
    float getGravity();
    int getX();
    int getY();
    int getZ();
    void printPlanet();

};

#endif 

#ifndef PLANET_H
#define PLANET_H



class Planet
{
private:
    //Population, object that describes behavior/preferences of planet's inhabitants 
    float size;
    //Entities[]; need containers for different types of units
    float terrain;
    float weather;
    float gravity;
     

    


 
public:
    Planet(int seed);
    //get population attributes
    float getTerrain();
    float getWeather();
    float getGravity();
    void printPlanet();

};

#endif 

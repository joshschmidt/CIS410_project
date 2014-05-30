#include "population.h"
#include <stdio.h>
#include <stdlib.h>

Population::Population(int setFlood, int setCivilian, int setMilitary)
{
	flood = setFlood;
	civilian = setCivilian;
	military = setMilitary;
}


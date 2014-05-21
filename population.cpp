#include "population.h"
#include <stdio.h>
#include <stdlib.h>

Population::Population(int setFlood, int setCivilian, int setMilitary)
{
	flood = setFlood;
	civilian = setCivilian;
	military = setMilitary;
}

// Facilitates combat between two populations
// Results written back to defenders population
// deletes attackers population
void Population::attack(Population* attackers,
			Population* defenders,
			float planetBonus)
{
	int flood = attackers->flood + defenders->flood;
	int civilian = attackers->civilian + defenders->civilian;
	int military = attackers->military + defenders->military;
	int humanCapability, floodCapability;
	// Flood attack
	if (attackers->flood != 0) {
		floodCapability = 0.25 * flood;
		humanCapability = planetBonus * military;
	} // Human Attack
	else {
		humanCapability = military;
		floodCapability = 0.25 * planetBonus * flood;
	}
	
	// Flood Victory
	if (floodCapability > humanCapability) {
		military = 0;
		// Add closed form damage equation here
		flood = flood / 2;
		flood += civilian * 0.75;
		civilian = 0;
	} 
	// Human Victory
	else {
		flood = 0;
		// Add closed form damage equation here
		military = military / 2;
	}
	
	// Writing back results
	defenders->flood = flood;
	defenders->civilian = civilian;
	defenders->military = military;
	
	delete attackers;
}

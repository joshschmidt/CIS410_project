#ifndef POPULATION_H
#define POPULATION_H

class Population
{
	private:
		int flood, civilian, military;
	public:
		Population(int setFlood, int setCivilian, int setMilitary);
		void attack(Population* attackers,
			  Population* defenders,
			  float planetBonus);
};
#endif

#ifndef POPULATION_H
#define POPULATION_H

class Population
{
	private:
		int flood, civilian, military;
	public:
		Population(int setFlood, int setCivilian, int setMilitary);
		int getFlood(){return flood;};
		int getCiv(){return civilian;};
		int getMilitary(){return military;};
};
#endif

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
		
		void setFlood(int f){flood = f;};
		void setCiv(int c){civilian = c;};
		void setMilitary(int m){military = m;};
};
#endif

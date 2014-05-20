#ifndef EVENT_H
#define EVENT_H



class Event
{
	private:
		int _type;
		float _time;
		int _planetID;
		int _galaxyID;
	     

	public:
		Event(int type, float time, int pID, int gID);
		

};

#endif


#pragma once
#ifndef __Tanks__
#define __Tanks__

#include "rt.h"

class 	Tanks {
private:
	struct theData {
		double volume;
	};

	CMutex	    *Mutex;	       // a pointer to a hidden mutex protecting the ‘Balance’ variable above
	CDataPool	*DataPool78;  // a datapool containing the data to be protected double balance; 
	theData		*ptr78;			// pointer to the data
	CDataPool	*DataPool80;  // a datapool containing the data to be protected double balance; 
	theData		*ptr80;			// pointer to the data
	CDataPool	*DataPool91;  // a datapool containing the data to be protected double balance; 
	theData		*ptr91;			// pointer to the data
	CDataPool	*DataPool97;  // a datapool containing the data to be protected double balance; 
	theData		*ptr97;			// pointer to the data

public:

	void decrement78(double amount) {
		Mutex->Wait();
		ptr78->volume = ptr78->volume - amount;
		Mutex->Signal();
	}
	void decrement80(double amount) {
		Mutex->Wait();
		ptr80->volume = ptr80->volume - amount;
		Mutex->Signal();
	}
	void decrement91(double amount) {
		Mutex->Wait();
		ptr91->volume = ptr91->volume - amount;
		Mutex->Signal();
	}
	void decrement97(double amount) {
		Mutex->Wait();
		ptr97->volume = ptr97->volume - amount;

		Mutex->Signal();
	}
	double read78() {
		double CurrentV;
		Mutex->Wait();
		CurrentV = ptr78->volume;
		Mutex->Signal();
		return CurrentV;
	}
	double read80() {
		double CurrentV;
		Mutex->Wait();
		CurrentV = ptr80->volume;
		Mutex->Signal();
		return CurrentV;
	}
	double read91() {
		double CurrentV;
		Mutex->Wait();
		CurrentV = ptr91->volume;
		Mutex->Signal();
		return CurrentV;
	}
	double read97() {
		double CurrentV;
		Mutex->Wait();
		CurrentV = ptr97->volume;
		Mutex->Signal();
		return CurrentV;
	}

	void refill() {
		Mutex->Wait();
		ptr78->volume = 500.0;
		ptr80->volume = 500.0;
		ptr91->volume = 500.0;
		ptr97->volume = 500.0;
		Mutex->Signal();
	}
	void refill78() {
		Mutex->Wait();
		ptr78->volume = 500.0;
		Mutex->Signal();
	}
	void refill80() {
		Mutex->Wait();
		ptr80->volume = 500.0;
		Mutex->Signal();
	}
	void refill91() {
		Mutex->Wait();
		ptr91->volume = 500.0;
		Mutex->Signal();
	}
	void refill97() {
		Mutex->Wait();
		ptr97->volume = 500.0;
		Mutex->Signal();
	}

	// constructor and destructor
	Tanks(string Name) {
		Mutex = new CMutex(string("__Mutex__") + string(Name));
		DataPool78 = new CDataPool(string("__DataPool78__") + string(Name), sizeof(struct theData));
		ptr78 = (struct theData *)(DataPool78->LinkDataPool());
		DataPool80 = new CDataPool(string("__DataPool80__") + string(Name), sizeof(struct theData));
		ptr80 = (struct theData *)(DataPool80->LinkDataPool());
		DataPool91 = new CDataPool(string("__DataPool91__") + string(Name), sizeof(struct theData));
		ptr91 = (struct theData *)(DataPool91->LinkDataPool());
		DataPool97 = new CDataPool(string("__DataPool97 __") + string(Name), sizeof(struct theData));
		ptr97 = (struct theData *)(DataPool97->LinkDataPool());
		Mutex->Wait();
		ptr78->volume = 500.0;
		ptr80->volume = 500.0;
		ptr91->volume = 500.0;
		ptr97->volume = 500.0;
		Mutex->Signal();

	}
	~Tanks() { /* delete mutex and datapool; */ }
};
#endif

#pragma once


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

	void decrement78(double amount) ;
	void decrement80(double amount);
	void decrement91(double amount);
	void decrement97(double amount);
	double read78() ;
	double read80() ;
	double read91() ;
	double read97() ;
	void refill() ;
	void refill78();
	void refill80() ;
	void refill91() ;
	void refill97() ;
	Tanks(string Name);
	~Tanks();
};
	void Tanks::decrement78(double amount) {
		Mutex->Wait();
		ptr78->volume = ptr78->volume - amount;
		Mutex->Signal();
	}
	void Tanks::decrement80(double amount) {
		Mutex->Wait();
		ptr80->volume = ptr80->volume - amount;
		Mutex->Signal();
	}

	void Tanks::decrement91(double amount) {
		Mutex->Wait();
		ptr91->volume = ptr91->volume - amount;
		Mutex->Signal();
	}

	void Tanks::decrement97(double amount) {
		Mutex->Wait();
		ptr97->volume = ptr97->volume - amount;

		Mutex->Signal();
	}

	double Tanks::read78() {
		double CurrentV;
		Mutex->Wait();
		CurrentV = ptr78->volume;
		Mutex->Signal();
		return CurrentV;
	}

	double Tanks::read80() {
		double CurrentV;
		Mutex->Wait();
		CurrentV = ptr80->volume;
		Mutex->Signal();
		return CurrentV;
	}

	double Tanks::read91() {
		double CurrentV;
		Mutex->Wait();
		CurrentV = ptr91->volume;
		Mutex->Signal();
		return CurrentV;
	}

	double Tanks::read97() {
		double CurrentV;
		Mutex->Wait();
		CurrentV = ptr97->volume;
		Mutex->Signal();
		return CurrentV;
	}

	void Tanks::refill() {
		Mutex->Wait();
		ptr78->volume = 500.0;
		ptr80->volume = 500.0;
		ptr91->volume = 500.0;
		ptr97->volume = 500.0;
		Mutex->Signal();
	}

	void Tanks::refill78() {
		Mutex->Wait();
		ptr78->volume = 500.0;
		Mutex->Signal();
	}

	void Tanks::refill80() {
		Mutex->Wait();
		ptr80->volume = 500.0;
		Mutex->Signal();
	}

	void Tanks::refill91() {
		Mutex->Wait();
		ptr91->volume = 500.0;
		Mutex->Signal();
	}

	void Tanks::refill97() {
		Mutex->Wait();
		ptr97->volume = 500.0;
		Mutex->Signal();
	}

	// constructor and destructor

	Tanks::Tanks(string Name) {
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

	Tanks::~Tanks() { /* delete mutex and datapool; */ }

#endif

#pragma once

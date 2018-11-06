#pragma once
#ifndef __Monitor__
#define __Monitor__

#include "..\rt.h"
#include "node.h"
#include "..\PumpDataPool.h"

#include<ctime>
#include <iostream>

#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_RESET   "\x1b[0m"

struct 	    Donestruct {
	PumpDataPool pool;

};
class 	MonitorScreen {
private:

	//needs int to print all the cars that are done
	//needs an array of struct for cars waiting

	List<char*> Pump1LL;
	List<char*> Pump2LL;
	List<char*> Pump3LL;
	List<char*> Pump4LL;
	int waitlistcount;
	List<char*>L0;
	List<PumpDataPool*>DONELL;


	/*struct theData {
		int x;	// the data to be protected
	};

	CDataPool	*DataPool;  // a datapool containing the data to be protected double balance; 
	theData		*ptr;			// pointer to the data

	*/
	CMutex	    *Mutex1;	       // a pointer to a hidden mutex protecting the ‘Balance’ variable above
	CMutex	    *Mutex2;	       // a pointer to a hidden mutex protecting the ‘Balance’ variable above
	CMutex	    *Mutex3;	       // a pointer to a hidden mutex protecting the ‘Balance’ variable above
	CMutex	    *Mutex4;	       // a pointer to a hidden mutex protecting the ‘Balance’ variable above
	CMutex	    *Mutex5;	       // a pointer to a hidden mutex protecting the ‘Balance’ variable above

	CMutex	    *MutexScreen;	       // a pointer to a hidden mutex protecting the ‘Balance’ variable above

public:

	void addtowaitlist(char* name, int x) {
	

		if (x == 1) {
			Mutex1->Wait();
			Pump1LL.Insert(name);
			Mutex1->Signal();
			}
		if (x == 2) {
			Mutex2->Wait();
			Pump2LL.Insert(name);
			Mutex2->Signal();
		}
		if (x == 3) {
			Mutex3->Wait();
			Pump3LL.Insert(name);
			Mutex3->Signal();
		}
		if (x == 4) {
			Mutex4->Wait();
			Pump4LL.Insert(name);
			Mutex4->Signal();
		}
		printwaitlist(x);
	}

	void deletenodewaitlist(int x) {


		if (x == 1) {
			Mutex1->Wait();
			Pump1LL.Deletefirst();
			Mutex1->Signal();
		}
		if (x == 2) {
			Mutex2->Wait();
			Pump2LL.Deletefirst();
			Mutex2->Signal();
		}
		if (x == 3) {
			Mutex3->Wait();
			Pump3LL.Deletefirst();
			Mutex3->Signal();
		}
		if (x == 4) {
			Mutex4->Wait();
			Pump4LL.Deletefirst();
			Mutex4->Signal();
		}
		printwaitlist(x);
	}
void addtodoneLL(PumpDataPool* cust) {
		Mutex5->Wait();
		DONELL.Insert(cust);
		Mutex5->Signal();
		printdoneLL();
	}

void printdoneLL() {
	int index;
	int x;
	Mutex5->Wait();

	index=DONELL.NumberofNodes();
	MutexScreen->Wait();
	for (x = 0; x <= index; x++) {
		MOVE_CURSOR(0, 40 + x);
		printf("%d %d\n", index, DONELL.Get(x)->creditcard);
	}
	MutexScreen->Signal();
	Mutex5->Signal();
}


void printcustinfo(PumpDataPool* cust,int cursorx,int cursory) {
	MutexScreen->Wait();
	MOVE_CURSOR(cursorx, cursory);
	printf(" ____ pumpnumber = %d \n", cust->pumpnumber);

	MOVE_CURSOR(cursorx, cursory+1);
	printf(" | %d | tankusing = %d \n", cust->pumpnumber, cust->tankusing);

	MOVE_CURSOR(cursorx, cursory + 2);
	printf("_|___|_status = %d \n", cust->status);

	MOVE_CURSOR(cursorx, cursory + 3);
	printf(" name ");
	for (int x = 0; x < 10; x++) {
		printf("%c", cust->name[x]);
	}
	printf("\n");
	MOVE_CURSOR(cursorx, cursory + 4);
	printf("credit card= %d         \n", cust->creditcard);

	MOVE_CURSOR(cursorx, cursory + 5);
	printf("volume = %f      \n", cust->volume);

	MutexScreen->Signal();
}
int waitlistindex(int x) {
	int index;

	if (x == 1) {
		Mutex1->Wait();
		index=Pump1LL.NumberofNodes();
		Mutex1->Signal();
	}
	if (x == 2) {
		Mutex2->Wait();
		index = Pump2LL.NumberofNodes();
		Mutex2->Signal();
	}
	if (x == 3) {
		Mutex3->Wait();
		index = Pump3LL.NumberofNodes();
		Mutex3->Signal();
	}
	if (x == 4) {
		Mutex4->Wait();
		index = Pump4LL.NumberofNodes();
		Mutex4->Signal();
	}
	MutexScreen->Wait();
	MOVE_CURSOR(0, 45);
	printf("%d", index);
	MutexScreen->Signal();
	return index;
}

void printtime() {

	int x;
	int time1;
	int seconds;
	int minutes;
	int hours;
	int yearsince1970;
	int year;
	int month = 0;
	int hourshere;

	time1 = (int)time(NULL);
	seconds = time1 % 60;
	time1 /= 60;

	minutes = time1 % 60;
	time1 /= 60;

	hours = time1 % 24;
	time1 /= 24;

	hourshere = hours - 8;
	if (hourshere < 0) {
		hourshere = 24 + hourshere;
	}
	yearsince1970 = time1 / 365;
	year = 1970 + yearsince1970;

	time1 = (time1 % 365) - 12;//days since jan 1 account for leapyears

	if (time1 < 31) {
		month = 1;
	}
	else
		time1 -= 31;
	if (time1 < 28) {
		if (month == 0)
			month = 2;
	}
	else
		time1 -= 28;

	if (time1 < 31) {
		if (month == 0)
			month = 3;
	}
	else
		time1 -= 31;

	if (time1 <= 30) {
		if (month == 0)
			month = 4;
	}
	else
		time1 -= 30;

	if (time1 <= 31) {
		if (month == 0)
			month = 5;
	}
	else
		time1 -= 31;
	if (time1 <= 30) {
		if (month == 0)
			month = 6;
	}
	else
		time1 -= 30;

	if (time1 <= 31) {
		if (month == 0)
			month = 7;
	}
	else
		time1 -= 31;
	if (time1 <= 31) {
		if (month == 0)
			month = 8;
	}
	else
		time1 -= 31;
	if (time1 <= 30) {
		if (month == 0)
			month = 9;
	}
	else
		time1 -= 30;

	if (time1 <= 31) {
		if (month == 0)
			month = 10;
	}
	else
		time1 -= 31;
	if (time1 <= 30) {
		if (month == 0)
			month = 11;
	}
	else
		time1 -= 30;

	if (time1 <= 31) {
		if (month == 0)
			month = 12;
	}
	else
		time1 -= 31;//
	
	MutexScreen->Wait();
	MOVE_CURSOR(0, 15);
	printf("Y%d M%d D%d H%d M%d  S%d  ", year, month, time1, hourshere, minutes, seconds);

	MutexScreen->Signal();
}

void printtank(int x, double vol) {
	MutexScreen->Wait();

	if (x == 78) {

		MOVE_CURSOR(0, 0);
	}
	else if (x == 80) {

		MOVE_CURSOR(0, 1);
	}
	else if (x == 91) {

		MOVE_CURSOR(0, 2);
	}
	else if (x == 97) {

		MOVE_CURSOR(0, 3);
	}
	if (vol < 200.0)
		printf(ANSI_COLOR_RED);
	else if (vol < 350.0)
		printf(ANSI_COLOR_YELLOW);
	else
		printf(ANSI_COLOR_GREEN);
	printf("tank%d %f ", x, vol);
	for (x = 0; x < 50; x++) {
		if (x <= (int)(vol / 10))
			printf("|");
		else
			printf(" ");
	}
	printf("\n" ANSI_COLOR_RESET);
	MutexScreen->Signal();

}
void printwaitlist(int x) {
	int index;
	int i;
	//int y;
	char *custname;
	if (x == 1) {

		

		Mutex1->Wait();
		index=Pump1LL.NumberofNodes();
		MutexScreen->Wait();
		//printf("%d", Pump1LL.NumberofNodes());
		//custname = Pump1LL.Get(0);
		//printf(" %s\n",custname);
		if (index != 0) {
			for (i = 0; i <= index; i++) {

				MOVE_CURSOR(0, 20 + i);
				printf("%d %d %s\n", index, i, Pump1LL.Get(i));
			}
		}

		else 

			MOVE_CURSOR(0, 20);
		printf("                \n");
		MutexScreen->Signal();
		Mutex1->Signal();
	}
	if (x == 2) {
		Mutex2->Wait();
		index = Pump2LL.NumberofNodes();
		MutexScreen->Wait();
		//printf("%d", Pump1LL.NumberofNodes());
		//custname = Pump1LL.Get(0);
		//printf(" %s\n",custname);

		for (i = 0; i <= index; i++) {

			MOVE_CURSOR(30, 20+i);
			printf("%d %d %s\n", index, i, Pump2LL.Get(i));
		}
		printf("              \n");

		MutexScreen->Signal();
		
		Mutex2->Signal();
	}
	if (x == 3) {
		Mutex3->Wait();
		index = Pump3LL.NumberofNodes();
		MutexScreen->Wait();

		for (i = 0; i <= index; i++) {

			MOVE_CURSOR(60, 20+i);
			printf("%d %d %s\n", index, i, Pump3LL.Get(i));
		}
		MOVE_CURSOR(60, 20 + i);

		printf("             \n");

		MutexScreen->Signal();

		//Pump3LL.Insert(name);
		Mutex3->Signal();
	}
	if (x == 4) {
		Mutex4->Wait();

		index = Pump4LL.NumberofNodes();
		MutexScreen->Wait();

		for (i = 0; i <= index; i++) {

			MOVE_CURSOR(90, 20+i);
			printf("%d %d %s\n", index, i, Pump4LL.Get(i));
		}
		printf("               \n");

		MutexScreen->Signal();
	//	Pump4LL.Insert(name);
		Mutex4->Signal();
	}
//	MutexScreen->Wait();


//	MutexScreen->Signal();

}
	

	// constructor and destructor
	MonitorScreen(string Name) {
		Mutex1 = new CMutex(string("__Mutex1__") + string(Name));
		Mutex2 = new CMutex(string("__Mutex2__") + string(Name));
		Mutex3 = new CMutex(string("__Mutex3__") + string(Name));
		Mutex4 = new CMutex(string("__Mutex4__") + string(Name));
		Mutex5 = new CMutex(string("__Mutex5__") + string(Name));
		MutexScreen = new CMutex("dosmuxP");

		
		
		
		//DataPool = new CDataPool(string("__DataPool__") + string(Name), sizeof(struct theData));
		//ptr = (struct theData *)(DataPool->LinkDataPool());
		


	}
	~MonitorScreen() { /* delete mutex and datapool; */ }
};
#endif


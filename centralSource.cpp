//Fonda Chau 15954143

//parent= gas station
//parent has child threads that are each pump, and grade tanks(4 of each)
//child is customers- active classes
#include <stdio.h>
#include "..\\rt.h"
#include "..\\PumpDataPool.h"
#include "..\\Tanks.h"
#include "PrintscreenMonitor.h"



//strings used in initiallizing semaphores
char PS1[4] = "PS1";
char PS2[4] = "PS2";
char PS3[4] = "PS3";
char PS4[4] = "PS4";
char CS1[4] = "CS1";
char CS2[4] = "CS2";
char CS3[4] = "CS3";
char CS4[4] = "CS4";

CMutex DoswindowMux("dosmuxP");
MonitorScreen screen("screen");

//initiallizing semaphores
CSemaphore		ps1(PS1, 0, 1);    // semaphore with initial value 0 and max value 1
CSemaphore		cs1(CS1, 1, 1);    // semaphore with initial value 1 and max value 1
CSemaphore		ps2(PS2, 0, 1);    // semaphore with initial value 0 and max value 1
CSemaphore		cs2(CS2, 1, 1);    // semaphore with initial value 1 and max value 1
CSemaphore		ps3(PS3, 0, 1);    // semaphore with initial value 0 and max value 1
CSemaphore		cs3(CS3, 1, 1);    // semaphore with initial value 1 and max value 1
CSemaphore		ps4(PS4, 0, 1);    // semaphore with initial value 0 and max value 1
CSemaphore		cs4(CS4, 1, 1);    // semaphore with initial value 1 and max value 1

//use to make sure that all pump datapools and created before reading
CRendezvous     RP("ReadPumpDP", 4);


//ChildThread1 to Childthread4
//reads datapool from datapool
UINT __stdcall ChildThread1(void *args) {
	
	CDataPool 		Pump1("Pump1", sizeof(struct PumpDataPool));
	struct PumpDataPool 	 *mypump1 = (struct PumpDataPool *)(Pump1.LinkDataPool());
	//int waitlist=0;
	//int finished = 0;
	int x;
	int i=0;
	int j = 0;
	PumpDataPool mystructsave[100];

	Donestruct savedonestruct[100];
	RP.Wait();
	PumpDataPool cust;
	while (1)
	{
		ps1.Wait();
		cust.creditcard = mypump1->creditcard;
		cust.pumpnumber = mypump1->pumpnumber;
		cust.status = mypump1->status;
		cust.tankusing = mypump1->tankusing;
		cust.volume = mypump1->volume;
		for ( x = 0; x < 10; x++) {
			cust.name[x] = mypump1->name[x];
		}
		cs1.Signal();
		if (cust.status == 9) {
			mystructsave[i].creditcard = mypump1->creditcard;
			mystructsave[i].pumpnumber = mypump1->pumpnumber;
			mystructsave[i].status = mypump1->status;
			mystructsave[i].tankusing = mypump1->tankusing;
			mystructsave[i].volume = mypump1->volume;
			for (x = 0; x < 10; x++) {
				mystructsave[i].name[x] = mypump1->name[x];
			}
			screen.addtowaitlist(&mystructsave[i].name[0],1);
			//screen.waitlistindex(1);
			i++;
		}
		else if (cust.status == 2) {
			screen.deletenodewaitlist(1);
		
		}
		else if (cust.status == 6) {
			mystructsave[j].creditcard = mypump1->creditcard;
			mystructsave[j].pumpnumber = mypump1->pumpnumber;
			mystructsave[j].status = mypump1->status;
			mystructsave[j].tankusing = mypump1->tankusing;
			mystructsave[j].volume = mypump1->volume;
			for (x = 0; x < 10; x++) {
				mystructsave[j].name[x] = mypump1->name[x];
			}

			savedonestruct[j].pool = mystructsave[j];
			screen.printtime(&savedonestruct[j]);
			screen.addtodoneLL(&savedonestruct[j]);
			j++;
		}
			//}
		if(cust.status!=9)
		screen.printcustinfo(&cust, 0, 5);

		//DoswindowMux.Signal();
		
	}
	return 0;
}
UINT __stdcall ChildThread2(void *args) {
	CDataPool 		Pump2("Pump2", sizeof(struct PumpDataPool));
	struct PumpDataPool 	 *mypump1 = (struct PumpDataPool *)(Pump2.LinkDataPool());
	int x;
	int i = 0;
	int j = 0;
	PumpDataPool mystructsave[100];

	Donestruct savedonestruct[100];
	RP.Wait();
	PumpDataPool cust;
	while (1)
	{
		ps2.Wait();
		cust.creditcard = mypump1->creditcard;
		cust.pumpnumber = mypump1->pumpnumber;
		cust.status = mypump1->status;
		cust.tankusing = mypump1->tankusing;
		cust.volume = mypump1->volume;
		for (x = 0; x < 10; x++) {
			cust.name[x] = mypump1->name[x];
		}
		cs2.Signal();
		if (cust.status == 9) {
			mystructsave[i].creditcard = mypump1->creditcard;
			mystructsave[i].pumpnumber = mypump1->pumpnumber;
			mystructsave[i].status = mypump1->status;
			mystructsave[i].tankusing = mypump1->tankusing;
			mystructsave[i].volume = mypump1->volume;
			for (x = 0; x < 10; x++) {
				mystructsave[i].name[x] = mypump1->name[x];
			}
			screen.addtowaitlist(&mystructsave[i].name[0], 2);
			//screen.waitlistindex(1);
			i++;
		}
		else if (cust.status == 2) {
			screen.deletenodewaitlist(2);
		
		}
		else if (cust.status == 6) {
			mystructsave[j].creditcard = mypump1->creditcard;
			mystructsave[j].pumpnumber = mypump1->pumpnumber;
			mystructsave[j].status = mypump1->status;
			mystructsave[j].tankusing = mypump1->tankusing;
			mystructsave[j].volume = mypump1->volume;
			for (x = 0; x < 10; x++) {
				mystructsave[j].name[x] = mypump1->name[x];
			}

			savedonestruct[j].pool = mystructsave[j];
			screen.printtime(&savedonestruct[j]);
			screen.addtodoneLL(&savedonestruct[j]);

			j++;
		}
		//}
		if (cust.status != 9)
			screen.printcustinfo(&cust, 30, 5);

		//DoswindowMux.Signal();

	}
	return 0;
}
UINT __stdcall ChildThread3(void *args) {

	CDataPool 		Pump3("Pump3", sizeof(struct PumpDataPool));
	struct PumpDataPool 	 *mypump1 = (struct PumpDataPool *)(Pump3.LinkDataPool());
	int x;
	int i = 0;
	int j = 0;
	PumpDataPool mystructsave[100];
	Donestruct savedonestruct[100];
	RP.Wait();
	PumpDataPool cust;
	while (1)
	{
		ps3.Wait();
		cust.creditcard = mypump1->creditcard;
		cust.pumpnumber = mypump1->pumpnumber;
		cust.status = mypump1->status;
		cust.tankusing = mypump1->tankusing;
		cust.volume = mypump1->volume;
		for (x = 0; x < 10; x++) {
			cust.name[x] = mypump1->name[x];
		}
		cs3.Signal();
		if (cust.status == 9) {
			mystructsave[i].creditcard = mypump1->creditcard;
			mystructsave[i].pumpnumber = mypump1->pumpnumber;
			mystructsave[i].status = mypump1->status;
			mystructsave[i].tankusing = mypump1->tankusing;
			mystructsave[i].volume = mypump1->volume;
			for (x = 0; x < 10; x++) {
				mystructsave[i].name[x] = mypump1->name[x];
			}
			screen.addtowaitlist(&mystructsave[i].name[0], 3);
			//screen.waitlistindex(1);
			i++;
		}
		else if (cust.status == 2) {
			screen.deletenodewaitlist(3);
		

		}
		else if (cust.status == 6) {
			mystructsave[j].creditcard = mypump1->creditcard;
			mystructsave[j].pumpnumber = mypump1->pumpnumber;
			mystructsave[j].status = mypump1->status;
			mystructsave[j].tankusing = mypump1->tankusing;
			mystructsave[j].volume = mypump1->volume;
			for (x = 0; x < 10; x++) {
				mystructsave[j].name[x] = mypump1->name[x];
			}
			savedonestruct[j].pool = mystructsave[j];
			screen.printtime(&savedonestruct[j]);
			screen.addtodoneLL(&savedonestruct[j]);

			j++;
		}
		//}
		if (cust.status != 9)
			screen.printcustinfo(&cust, 60, 5);

		//DoswindowMux.Signal();

	}
	return 0;
}
UINT __stdcall ChildThread4(void *args) {

	CDataPool 		Pump4("Pump4", sizeof(struct PumpDataPool));
	struct PumpDataPool 	 *mypump1 = (struct PumpDataPool *)(Pump4.LinkDataPool());
	int x;
	int i = 0;
	int j = 0;
	PumpDataPool mystructsave[100];

	Donestruct savedonestruct[100];
	RP.Wait();
	PumpDataPool cust;
	while (1)
	{
		ps4.Wait();
		cust.creditcard = mypump1->creditcard;
		cust.pumpnumber = mypump1->pumpnumber;
		cust.status = mypump1->status;
		cust.tankusing = mypump1->tankusing;
		cust.volume = mypump1->volume;
		for (x = 0; x < 10; x++) {
			cust.name[x] = mypump1->name[x];
		}
		cs4.Signal();
		if (cust.status == 9) {
			mystructsave[i].creditcard = mypump1->creditcard;
			mystructsave[i].pumpnumber = mypump1->pumpnumber;
			mystructsave[i].status = mypump1->status;
			mystructsave[i].tankusing = mypump1->tankusing;
			mystructsave[i].volume = mypump1->volume;
			for (x = 0; x < 10; x++) {
				mystructsave[i].name[x] = mypump1->name[x];
			}
			screen.addtowaitlist(&mystructsave[i].name[0], 4);
			//screen.waitlistindex(1);
			i++;
		}
		else if (cust.status == 2) {
			screen.deletenodewaitlist(4);


		}
		else if (cust.status == 6) {
			mystructsave[j].creditcard = mypump1->creditcard;
			mystructsave[j].pumpnumber = mypump1->pumpnumber;
			mystructsave[j].status = mypump1->status;
			mystructsave[j].tankusing = mypump1->tankusing;
			mystructsave[j].volume = mypump1->volume;
			for (x = 0; x < 10; x++) {
				mystructsave[j].name[x] = mypump1->name[x];
			}

			savedonestruct[j].pool = mystructsave[j];
			screen.printtime(&savedonestruct[j]);
			screen.addtodoneLL(&savedonestruct[j]);

			j++;
		}
		//}
		if (cust.status != 9)
			screen.printcustinfo(&cust, 90, 5);
		
		//DoswindowMux.Signal();

	}
	return 0;
}

UINT __stdcall ChildThread5(void *args) {
	//char gotchar;
	char KeyData[4] = { '\0', '\0','\0', '\0' };// a 2 character keyboard command initialised to be emptyin
	Tanks Tanks1("Tanks");		// a monitor with built in synchronisation	
	//int x;
	int count=0;
	while (1) {

		double tank78vol;
		double tank80vol;
		double tank91vol;
		double tank97vol;
		tank78vol = Tanks1.read78();
		tank80vol = Tanks1.read80();
		tank91vol = Tanks1.read91();
		tank97vol = Tanks1.read97();

		screen.printtank(78, tank78vol);

		screen.printtank(80, tank80vol);
		screen.printtank(91, tank91vol);
		screen.printtank(97, tank97vol);
		if (TEST_FOR_KEYBOARD() != 0) {
			count++;
			KeyData[3] = KeyData[2];// move up previous character read
			KeyData[2] = KeyData[1];// move up previous character read
			KeyData[1] = KeyData[0];// move up previous character read
			KeyData[0] = _getch();// read next character from keyboard}}
			SLEEP(250);
			DoswindowMux.Wait();
			MOVE_CURSOR(0, 31);
			printf("%d %d %c %c %c %c", TEST_FOR_KEYBOARD(),count,KeyData[0], KeyData[1], KeyData[2], KeyData[3]);
			DoswindowMux.Signal();
				if ((KeyData[1] == 'r'&&KeyData[3] == 'f' )|| (KeyData[3] == 'r'&&KeyData[1] == 'f') ){
					Tanks1.refill();
					KeyData[0] = '\0';// move up previous character read
					KeyData[1] = '\0';// read next character from keyboard}}

				}

				if ((KeyData[1] == '1'&&KeyData[3] == 'f') || (KeyData[3] == '1'&&KeyData[1] == 'f')) {
					Tanks1.refill78();
					KeyData[0] = '\0';// move up previous character read
					KeyData[1] = '\0';// read next character from keyboard}}

				}
				if ((KeyData[1] == '2'&&KeyData[3] == 'f') || (KeyData[3] == '2'&&KeyData[1] == 'f')) {
					Tanks1.refill80();
					KeyData[0] = '\0';// move up previous character read
					KeyData[1] = '\0';// read next character from keyboard}}

				}
				if ((KeyData[1] == '3'&&KeyData[3] == 'f' )|| (KeyData[3] == '3'&&KeyData[1] == 'f')) {
					Tanks1.refill91();
					KeyData[0] = '\0';// move up previous character read
					KeyData[1] = '\0';// read next character from keyboard}}

				}
				if ((KeyData[1] == '4'&&KeyData[3] == 'f' )|| (KeyData[3] == '4'&&KeyData[1] == 'f')) {
					Tanks1.refill97();
					KeyData[0] = '\0';// move up previous character read
					KeyData[1] = '\0';// read next character from keyboard}}

				}
				if ((KeyData[1] == 's'&&KeyData[3] == 'c') || (KeyData[3] == 's'&&KeyData[1] == 'c')) {
					DoswindowMux.Wait();

					CLEAR_SCREEN();
					DoswindowMux.Signal();
				}




			//SLEEP(5000);
		}
				//}

		/*
		if (KeyData[0] == 'r') {
			Tanks1.refill();
			KeyData[0] = '\0';
		}

		if (KeyData[0] == '1') {
			Tanks1.refill78();
			KeyData[0] = '\0';
		}
		if ( KeyData[0] == '2') {
			Tanks1.refill80();
			KeyData[0] = '\0';
		}
		if (KeyData[0] == '3') {
			Tanks1.refill91();
			KeyData[0] = '\0';
		}
		if (KeyData[0] == '4') {
			Tanks1.refill97();
			KeyData[0] = '\0';
		}

		*/

	}
	return 0;
}

/*
    __
 .-'--`-._
 '-O---O--'

*/
int main() {
	Donestruct tempstore;
	CProcess p1("..\\Debug\\pumps.exe",	// pathlist to child program executable				
		NORMAL_PRIORITY_CLASS,			// priority
		OWN_WINDOW,						// process has its own window					
		ACTIVE							// process is active immediately
	);

	CProcess p2("..\\Debug\\Customer.exe",	// pathlist to child program executable				
		NORMAL_PRIORITY_CLASS,			// priority
		PARENT_WINDOW,						// process has its own window					
		ACTIVE							// process is active immediately
	);

	CThread T1(ChildThread1, ACTIVE, NULL);
	CThread T2(ChildThread2, ACTIVE, NULL);
	CThread T3(ChildThread3, ACTIVE, NULL);
	CThread T4(ChildThread4, ACTIVE, NULL);
	CThread T5(ChildThread5, ACTIVE, NULL);


	while (1) {
		screen.printtime(&tempstore);

	}
	p1.WaitForProcess();
	p2.WaitForProcess();
	return 0;
}

int* getdate() {
	int result[6];
	
//	printf("Y%d M%d D%d H%d M%d S%d", year, month, time1, hourshere, minutes, seconds);
	return &result[0];
}
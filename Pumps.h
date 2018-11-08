//Fonda Chau 15954143

#include <stdio.h>
#include "..\\PumpDataPool.h"
#include "..\\rt.h"
#include "..\\Customer.h"
#include "..\\Tanks.h"

//used to make sure that all pumps are made untill reading of pipelines begin
CRendezvous     r1("MakePump", 4);
CMutex DoswindowMux("dosmux");

char PS1[4] = "PS1";
char PS2[4] = "PS2";
char PS3[4] = "PS3";
char PS4[4] = "PS4";
char CS1[4] = "CS1";
char CS2[4] = "CS2";
char CS3[4] = "CS3";
char CS4[4] = "CS4";

#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_RESET   "\x1b[0m"


Tanks Tanks1("Tanks");		// a monitor with built in synchronisation	


UINT __stdcall ChildThread(void *args) {
	//int i;
	//char name[15];
	struct customerdetails mystruct;
	char *TheMessage = (char *)(args);
	//CPipe	P1(TheMessage, 1024);							// Create a pipe 'p1' with the name "MyPipe"
	int cursorx;
	int cursory;
	CTypedPipe <customerdetails> P1(TheMessage, 100);
	CTypedPipe <customerdetails> PR1(TheMessage+string("R"), 100);

	r1.Wait();
	while (1) {
		P1.Read(&mystruct);	// Read the structure from the pipeline
		
		//if (mystruct.status == 1) {
			//PR1.Write(&mystruct);

//		}
		//else if (mystruct.status == 9) {
			//PR1.Write(&mystruct);

		//}
		//else
		//{
			PR1.Write(&mystruct);

			if (mystruct.pumpusing == 1) {
				cursorx = 20;
				cursory = 0;
			}
			else if (mystruct.pumpusing == 2) {
				cursorx = 70;
				cursory = 0;
			}
			else if (mystruct.pumpusing == 3) {

				cursorx = 20;
				cursory = 20;
			}
			else {
				cursorx = 70;
				cursory = 20;
			}

			if (mystruct.status == 0) {
				DoswindowMux.Wait();
				MOVE_CURSOR(cursorx, cursory);
				printf("%s Thread read        ", TheMessage);
				MOVE_CURSOR(cursorx, cursory + 1);
				printf(" pump is free         ");
				MOVE_CURSOR(cursorx, cursory + 2);
				printf("                      \n");
				MOVE_CURSOR(cursorx, cursory + 3);
				printf("                      \n");
				MOVE_CURSOR(cursorx, cursory + 5);
				printf("                      \n");
				MOVE_CURSOR(cursorx, cursory + 6);
				printf("                      \n");
				MOVE_CURSOR(cursorx, cursory + 7);
				printf("                      \n");
				MOVE_CURSOR(cursorx, cursory + 8);
				printf("                      \n");
				DoswindowMux.Signal();
			}
			else {

				DoswindowMux.Wait();
				MOVE_CURSOR(cursorx, cursory);
				if (mystruct.status == 1) {
					printf("Arrival at pump       \n");
				}
				else if (mystruct.status == 2) {
					printf("swiping a credit card \n");
				}
				else if (mystruct.status == 3) {
					printf("removing the gas hose \n");
				}
				else if (mystruct.status == 4) {
					printf("selecting a grade     \n");
				}
				else if (mystruct.status == 5) {
					printf("dispensing fuel       \n");
				}
				else if (mystruct.status == 6) {
					printf("returning the hose    \n");
				}
				MOVE_CURSOR(cursorx, cursory + 1);
				
				printf(" desiredgrade = %d", mystruct.desiredgrade);
				MOVE_CURSOR(cursorx, cursory + 2);
				printf(" creditcare %d", mystruct.creditcard);
				MOVE_CURSOR(cursorx, cursory + 3);
				printf(" name ");
				for (int x = 0; x < 10; x++) {
					printf("%c", mystruct.name[x]);
				}
				
				MOVE_CURSOR(cursorx, cursory + 5);
				/*if (mystruct.color == 0) {
					printf(ANSI_COLOR_RED);
				}
				else if (mystruct.color == 1) {
					printf(ANSI_COLOR_RESET);
				}
				else if (mystruct.color == 2) {
					printf(ANSI_COLOR_YELLOW);
				}
				else if (mystruct.color == 3) {
					printf(ANSI_COLOR_BLUE);
				}
				else if (mystruct.color == 4) {
					printf(ANSI_COLOR_MAGENTA);
				}
				else if (mystruct.color == 5) {
					printf(ANSI_COLOR_CYAN);
				}
				else
					printf(ANSI_COLOR_GREEN);
*/
				printf("       _________\n");
				MOVE_CURSOR(cursorx, cursory + 6);
				printf("____ /_____|___\\___\n");
				MOVE_CURSOR(cursorx, cursory + 7);
				printf("O   _   -  |  _   ,*\n");
				MOVE_CURSOR(cursorx, cursory + 8);
				printf("'--(_)-------(_)--'\n");
				//printf(ANSI_COLOR_RESET);

				DoswindowMux.Signal();
			}
		//}
		
	}
	return 0;
}


class Pump :public ActiveClass {

private:
	char * pumpName; //pump 1 to 4
	char * pipeName;
	char pipe[10];

	char EntryGate[11];
	char ExitGate[10];
	char Empty[7];
	char Full[6];

	char PS[4];
	char CS[4];
	char MUTEX[4];
	int pumpnumber;
	int flag=0;
	int connected;
	int desiredtank=0; // grade in which to fill (from tank)
	int status = 0; //filling or free
public:
	Pump(char *number, int i, int j, int k);
	//void set(int j, int k);
	//void usepump(char*pipe);
	int main(void);
};

Pump::Pump(char*number, int i, int j, int k) {
	pumpName = number;
	pumpnumber = i;
	desiredtank = j; // grade in which to fill (from tank)
	status = k;
	int cursorx;
	int cursory;
	if (pumpnumber == 1) {
		strcpy_s(pipe, pipe1); 
		strcpy_s(PS, PS1);
		strcpy_s(CS, CS1);
		
		strcpy_s(EntryGate, EntryGate1);
		strcpy_s(ExitGate, ExitGate1);
		strcpy_s(Empty, Empty1);
		strcpy_s(Full, Full1);
		cursorx = 0;
		cursory = 0;
		//strcpy_s(MUTEX, MUTEX1);
	}
	else if (pumpnumber == 2) {
		strcpy_s(pipe, pipe2); 
		strcpy_s(PS, PS2);
		strcpy_s(CS, CS2);
		strcpy_s(EntryGate, EntryGate2);
		strcpy_s(ExitGate, ExitGate2);
		strcpy_s(Empty, Empty2);
		strcpy_s(Full, Full2);


		cursorx = 50;
		cursory = 0;
		//strcpy_s(MUTEX, MUTEX2);
	}
	else if (pumpnumber == 3) {
		strcpy_s(pipe, pipe3); 
		strcpy_s(PS, PS3);
		strcpy_s(CS, CS3);
		strcpy_s(EntryGate, EntryGate3);
		strcpy_s(ExitGate, ExitGate3);
		strcpy_s(Empty, Empty3);
		strcpy_s(Full, Full3);

		cursorx = 0;
		cursory = 20;
		//strcpy_s(MUTEX, MUTEX3);
	}
	else {
		strcpy_s(pipe, pipe4); 
		strcpy_s(PS, PS4);
		strcpy_s(CS, CS4); 
		strcpy_s(EntryGate, EntryGate4);
		strcpy_s(ExitGate, ExitGate4);
		strcpy_s(Empty, Empty4);
		strcpy_s(Full, Full4);

		cursorx = 50;
		cursory = 20;
		//strcpy_s(MUTEX, MUTEX4);
	}
	DoswindowMux.Wait();
	MOVE_CURSOR(cursorx, cursory+1);
	printf(" _____________ \n");
	MOVE_CURSOR(cursorx, cursory+2);
	printf(" |   _____   | \n");
	MOVE_CURSOR(cursorx, cursory+3);
	printf(" |   |   |   | \n");
	MOVE_CURSOR(cursorx, cursory+4);
	printf(" |   | %d |   |\\ \n", pumpnumber);
	MOVE_CURSOR(cursorx, cursory+5);
	printf(" |   |___|   | \\ \n");
	MOVE_CURSOR(cursorx, cursory+6);
	printf(" |           |  | \n");
	MOVE_CURSOR(cursorx, cursory+7);
	printf(" |           |  / \n");
	MOVE_CURSOR(cursorx, cursory+8);
	printf(" |           | / \n");
	MOVE_CURSOR(cursorx, cursory+9);
	printf(" |           |/ \n");
	MOVE_CURSOR(cursorx, cursory+10);
	printf("------------ - \n");//fflush(stdout);// force output to be written to screen
	fflush(stdout);// force output to be written to screen
	DoswindowMux.Signal();
	
}


int Pump::main(void) {
	{
		int cursorx;
		int cursory;
		double gasprice=0.0;
		double pumpedvol=0.0;


		CDataPool 		Pump1(pumpName, sizeof(struct PumpDataPool));
		struct PumpDataPool 	 *mypump = (struct PumpDataPool *)(Pump1.LinkDataPool());

		if (pumpnumber == 1) {
			cursorx = 1;
			cursory = 12;
		}
		else if (pumpnumber == 2) {
			cursorx = 50;
			cursory = 12;

		}
		else if (pumpnumber == 3) {
			cursorx = 1;
			cursory = 32;}
		else{
			cursorx = 50;
			cursory = 32;
		}
		DoswindowMux.Wait();
		MOVE_CURSOR(cursorx, cursory);
		printf("create/use the datapool\n");
		MOVE_CURSOR(cursorx, cursory + 1);
		printf("linked to datapool at %p\n", mypump);
		MOVE_CURSOR(cursorx, cursory + 2);
		printf("created child tread to read pipeline\n");
		DoswindowMux.Signal();
		CThread T1(ChildThread, ACTIVE, pipe);
		//r1.Wait();
		CSemaphore		ps1(PS, 0, 1);    // semaphore with initial value 0 and max value 1
		CSemaphore		cs1(CS, 1, 1);    // semaphore with initial value 1 and max value 1
		CSemaphore		psb(PS+string("b"), 0, 1);    // semaphore with initial value 0 and max value 1
		CSemaphore		csb(CS + string("b"), 1, 1);    // semaphore with initial value 1 and max value 1

		CSemaphore   EntryGate(EntryGate, 0, 1);
		CSemaphore   ExitGate(ExitGate, 0, 1);
		CSemaphore   Empty(Empty, 0, 1);
		CSemaphore   Full(Full, 0, 1);


		
		CTypedPipe <customerdetails> PR1(pipe + string("R"), 100);
		struct customerdetails mystruct;
		CTypedPipe <double> PCR1(pipe + string("CR"), 100);

		EntryGate.Signal();
		
		while (1) {
				PR1.Read(&mystruct);	// Read the structure from the pipeline
				
				if (mystruct.status == 1) {
					Full.Wait();
					while ((Tanks1.read78() < 200) || (Tanks1.read80() < 200) || (Tanks1.read91() < 200) || (Tanks1.read97() < 200)) {
					}
					pumpedvol = 0.0;
				}
				if (mystruct.status == 5) {
					if (mystruct.desiredgrade == 78) {
						Tanks1.decrement78(0.5);
						pumpedvol = pumpedvol + 0.5;
					}
					else if (mystruct.desiredgrade == 80) {
						Tanks1.decrement80(0.5);
						pumpedvol = pumpedvol + 0.5;
					}
					else if (mystruct.desiredgrade == 91) {
						Tanks1.decrement91(0.5);
						pumpedvol = pumpedvol + 0.5;
					}
					else if (mystruct.desiredgrade == 97) {
						Tanks1.decrement97(0.5);
						pumpedvol = pumpedvol + 0.5;
					}

					PCR1.Write(&pumpedvol);
					//SLEEP(500);
				}

				if (mystruct.status == 0) {
					pumpedvol = 0;
					ExitGate.Signal();
					
					Empty.Wait();

					EntryGate.Signal();

				}
				DoswindowMux.Wait();
				MOVE_CURSOR(cursorx, cursory + 3);
				printf("gas rate:%.2lf, cost:%.2lf", gasprice, gasprice*pumpedvol);
				DoswindowMux.Signal();
				cs1.Wait();
				mypump->pumpnumber = pumpnumber;
				mypump->status = mystruct.status;
				mypump->tankusing = mystruct.desiredgrade;
				mypump->creditcard = mystruct.creditcard;
				mypump->volume = pumpedvol;
				for (int x = 0; x < 10; x++) {
					mypump->name[x] = mystruct.name[x];
				}
				ps1.Signal();

				if (mystruct.status == 4) {
					psb.Wait();
					gasprice = mypump->baseprice;
					csb.Signal();
				}

		}
		return 0;
	}
}

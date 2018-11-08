//Fonda Chau 15954143

#pragma once
#include 	<stdio.h>
#include "rt.h"

struct 	    customerdetails {
	char name[10];
	int desiredgrade;
	int creditcard;
	int pumpusing;
	int status;
	int color;
};
/*		printf("Arrival at pump\n"); status=1
		printf("swiping a credit card\n"); status=2
		printf("removing the gas hose from the pump\n"); status=3
		printf("selecting a grade of fuel\n"); status=4
		printf("dispensing fuel\n"); status=5
		printf("returning the hose to the pump\n"); status =6
		printf("driving away\n"); status =0 ie no car there
*/



char pipe1[10] = "pipe1";
char pipe2[10] = "pipe2";
char pipe3[10] = "pipe3";
char pipe4[10] = "pipe4";

char MUTEX1[4] = "MT1";
char MUTEX2[4] = "MT2";
char MUTEX3[4] = "MT3";
char MUTEX4[4] = "MT4"; 
char NullName[10] = "         ";


char EntryGate1[11] = "EntryGate1";
char ExitGate1[10] = "ExitGate1";
char Empty1[7] = "Empty1";
char Full1[6] = "Full1";

char EntryGate2[11] = "EntryGate2";
char ExitGate2[10] = "ExitGate2";
char Empty2[7] = "Empty2";
char Full2[6] = "Full2";

char EntryGate3[11] = "EntryGate3";
char ExitGate3[10] = "ExitGate3";
char Empty3[7] = "Empty3";
char Full3[6] = "Full3";

char EntryGate4[11] = "EntryGate4";
char ExitGate4[10] = "ExitGate4";
char Empty4[7] = "Empty4";
char Full4[6] = "Full4";


class Customer :public ActiveClass {

private:
	char carname[10];
	int desiredgrade;
	int creditcard;
	int carcolor;
	int pumpusing;
	char pipe[10];
	char MUTEX[4];
	double desiredVol;

	char EntryGate[11];
	char ExitGate[10];
	char Empty[7];
	char Full[6];
public:
	Customer(int creditcardnumber, char customername[10], int desiredgasgrade, int assignedpump, double desiredvolume,int color);
	int main();
	// getpump();
};


Customer::Customer(int creditcardnumber, char customername[10], int desiredgasgrade, int assignedpump, double desiredvolume,int color) {
	desiredVol = desiredvolume;
	desiredgrade = desiredgasgrade;
	creditcard = creditcardnumber;
	pumpusing = assignedpump;
	carcolor = color;
	
	strcpy_s(carname, customername);

	if (pumpusing == 1) {
		strcpy_s(pipe, pipe1);
		strcpy_s(MUTEX, MUTEX1);

		strcpy_s(EntryGate, EntryGate1);
		strcpy_s(ExitGate, ExitGate1);
		strcpy_s(Empty, Empty1);
		strcpy_s(Full, Full1);
	}
	else if (pumpusing == 2) {
		strcpy_s(pipe, pipe2);
		strcpy_s(MUTEX, MUTEX2);

		strcpy_s(EntryGate, EntryGate2);
		strcpy_s(ExitGate, ExitGate2);
		strcpy_s(Empty, Empty2);
		strcpy_s(Full, Full2);
	}
	else if (pumpusing == 3) {
		strcpy_s(pipe, pipe3);
		strcpy_s(MUTEX, MUTEX3);

		strcpy_s(EntryGate, EntryGate3);
		strcpy_s(ExitGate, ExitGate3);
		strcpy_s(Empty, Empty3);
		strcpy_s(Full, Full3);
	}
	else {
		strcpy_s(pipe, pipe4);
		strcpy_s(MUTEX, MUTEX4);

		strcpy_s(EntryGate, EntryGate4);
		strcpy_s(ExitGate, ExitGate4);
		strcpy_s(Empty, Empty4);
		strcpy_s(Full, Full4);
	}
};

int Customer::main() {
	CMutex M1(MUTEX);
	CTypedPipe <customerdetails> P1(pipe, 100);
	CTypedPipe <double> PCR1(pipe + string("CR"), 100);
	struct customerdetails mystruct;


	CSemaphore   EntryGate(EntryGate, 0, 1);
	CSemaphore   ExitGate(ExitGate, 0, 1);
	CSemaphore   Empty(Empty, 0, 1);
	CSemaphore   Full(Full, 0, 1);

	


	double recievedvolume;
	mystruct.status = 9;
	for (int x = 0; x < 10; x++) {
		mystruct.name[x] = carname[x];
	}
	mystruct.desiredgrade = 0;
	mystruct.pumpusing = pumpusing;
	mystruct.creditcard = 0;
	mystruct.color = carcolor;

	M1.Wait();
	P1.Write(&mystruct);			// write the structure to the pipeline
	M1.Signal();
	EntryGate.Wait(); //wait for free pump
	mystruct.status = 1;

	SLEEP(1000);
	M1.Wait();
	P1.Write(&mystruct);			// write the structure to the pipeline
	M1.Signal();

	
	Full.Signal(); //use pump

	
	


	mystruct.status = 2;
	mystruct.creditcard = creditcard;

	SLEEP(1000);
	M1.Wait();
	P1.Write(&mystruct);			// write the structure to the pipeline
	M1.Signal();

	mystruct.status = 3;

	SLEEP(1000);
	M1.Wait();
	P1.Write(&mystruct);			// write the structure to the pipeline
	M1.Signal();

	mystruct.status = 4;
	mystruct.desiredgrade = desiredgrade;

	SLEEP(1000);
	M1.Wait();
	P1.Write(&mystruct);			// write the structure to the pipeline
	M1.Signal();
	
	mystruct.status = 5;
	SLEEP(1000);


	M1.Wait();
	P1.Write(&mystruct);			// write the structure to the pipeline
	M1.Signal();
	//SLEEP(1000);
	PCR1.Read(&recievedvolume);
	while (desiredVol > recievedvolume) {
		M1.Wait();
		P1.Write(&mystruct);			// write the structure to the pipeline
		M1.Signal();
		PCR1.Read(&recievedvolume);

	}

	mystruct.status = 6;
	SLEEP(1000);


	M1.Wait();
	P1.Write(&mystruct);			// write the structure to the pipeline
	M1.Signal();
	
	mystruct.status = 0;
	for (int x = 0; x < 10; x++) {
		mystruct.name[x] = NullName[x];
	}
	mystruct.desiredgrade = 0;
	mystruct.creditcard = 0;
	SLEEP(1000);

	M1.Wait();
	P1.Write(&mystruct);			// write the structure to the pipeline
	M1.Signal();	
	ExitGate.Wait();//wait to get off
	Empty.Signal();//leave seat
	
	SLEEP(1000);

	
	return 0;
}
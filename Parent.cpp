//Fonda Chau 15954143

//parent= gas station
//parent has child threads that are each pump, and grade tanks(4 of each)
//child is customers- active classes
#include <stdio.h>
#include "C:\\Users\\Fonda\\Documents\\School\\YEAR4\\CPEN333\\Assignment1\\rt.h"
#include "tankDataPool.h"
#include "PumpDataPool.h"
#include "Pumps.h"
#include "Customer.h"

//#define ANSI_COLOR_RED     "\x1b[31m"
//#define ANSI_COLOR_GREEN   "\x1b[32m"

int main(){

	char pump1data[] = "Pump1";
	//char pipe1data[] = "Pipe1";
	printf("creating child process %s\n", pump1data);
	Pump PumpProcess1(pump1data);
	//Pump PumpProcess1(pump1data, pipe1data);
	PumpProcess1.Resume();
	CDataPool 		Pump1(pump1data, sizeof(struct PumpDataPool));
	printf("Parent attempting to create/use the datapool for tank .....\n");
	struct PumpDataPool 	 *mypump1 = (struct PumpDataPool *)(Pump1.LinkDataPool());
	printf("Parent linked to datapool of pump at address %p.....\n", mypump1);

	char pump2data[] = "Pump2";
	//char pipe2data[] = "Pipe2";
	printf("creating child process %s\n", pump2data);
	Pump PumpProcess2(pump2data);// , Pump2("Pump2"), Pump3("Pump3"), Pump4("Pump4");
	//Pump PumpProcess2(pump2data, pipe2data);// , Pump2("Pump2"), Pump3("Pump3"), Pump4("Pump4");
	PumpProcess2.Resume();
	CDataPool 		Pump2("Pump2", sizeof(struct PumpDataPool));
	printf("Parent attempting to create/use the datapool for tank .....\n");
	struct PumpDataPool 	 *mypump2 = (struct PumpDataPool *)(Pump2.LinkDataPool());
	printf("Parent linked to datapool of pump at address %p.....\n", mypump2);

	char pump3data[] = "Pump3";
	//char pipe3data[] = "Pipe3";
	printf("creating child process %s\n", pump3data);
	Pump PumpProcess3(pump3data);// , Pump2("Pump2"), Pump3("Pump3"), Pump4("Pump4");
	//Pump PumpProcess3(pump3data, pipe3data);// , Pump2("Pump2"), Pump3("Pump3"), Pump4("Pump4");
	PumpProcess3.Resume();
	CDataPool 		Pump3("Pump3", sizeof(struct PumpDataPool));
	printf("Parent attempting to create/use the datapool for tank .....\n");
	struct PumpDataPool 	 *mypump3 = (struct PumpDataPool *)(Pump3.LinkDataPool());
	printf("Parent linked to datapool of pump at address %p.....\n", mypump3);

	char pump4data[] = "Pump4";
	//char pipe4data[] = "Pipe4";
	printf("creating child process %s\n", pump4data);
	Pump PumpProcess4(pump4data);// , Pump2("Pump2"), Pump3("Pump3"), Pump4("Pump4");
	//Pump PumpProcess4(pump4data, pipe4data);// , Pump2("Pump2"), Pump3("Pump3"), Pump4("Pump4");
	PumpProcess4.Resume();
	CDataPool 		Pump4("Pump4", sizeof(struct PumpDataPool));
	printf("Parent attempting to create/use the datapool for tank .....\n");
	struct PumpDataPool 	 *mypump4 = (struct PumpDataPool *)(Pump4.LinkDataPool());
	printf("Parent linked to datapool of pump at address %p.....\n", mypump4);

	PumpProcess1.set(1, 2, 3);

	PumpProcess2.set(5, 6, 7);

	PumpProcess3.set(3, 2, 1);
	PumpProcess4.set(9, 8, 10);
	getchar();
	printf("Parents read pump1 pumpnumber = %d\n", mypump1->pumpnumber);
	printf("parents read pump1 tankusing = %d\n", mypump1->tankusing);
	printf("parents read pump1 status = %d\n", mypump1->status);

	printf("Parents read pump2 pumpnumber = %d\n", mypump2->pumpnumber);
	printf("parents read pump2 tankusing = %d\n", mypump2->tankusing);
	printf("parents read pump2 status = %d\n", mypump2->status);

	printf("Parents read pump3 pumpnumber = %d\n", mypump3->pumpnumber);
	printf("parents read pump3 tankusing = %d\n", mypump3->tankusing);
	printf("parents read pump3 status = %d\n", mypump3->status);

	printf("Parents read pump4 pumpnumber = %d\n", mypump4->pumpnumber);
	printf("parents read pump4 tankusing = %d\n", mypump4->tankusing);
	printf("parents read pump4 status = %d\n", mypump4->status);
	
	/*char bob[] = "bob";
	Customer customerbob(10123321, bob, 78, 1);
	customerbob.Resume();
	PumpProcess1.usepump(bob);*/

	
	/*char tim[] = "tim";
	Customer customertim(12345678, tim, 81, 2);
	customertim.Resume();
	PumpProcess2.usepump(tim);*/

	/*printf("Parent attempting to create/use the datapool for tanks 1.....\n");
	CDataPool 		tank1("tank1", sizeof(struct tankDataPool));
	printf("Parent attempting to create/use the datapool for tanks 2.....\n");
	CDataPool 		tank2("tank2", sizeof(struct tankDataPool));
	printf("Parent attempting to create/use the datapool for tanks 3.....\n");
	CDataPool 		tank3("tank3", sizeof(struct tankDataPool));
	printf("Parent attempting to create/use the datapool for tanks 4.....\n");
	CDataPool 		tank4("tank4", sizeof(struct tankDataPool));

	struct tankDataPool 	 *mytank1 = (struct tankDataPool *)(tank1.LinkDataPool());
	printf("Parent linked to datapool of tank 1 at address %p.....\n", mytank1);
	struct tankDataPool 	 *mytank2 = (struct tankDataPool *)(tank2.LinkDataPool());
	printf("Parent linked to datapool of tank 2 at address %p.....\n", mytank2);
	struct tankDataPool 	 *mytank3 = (struct tankDataPool *)(tank3.LinkDataPool());
	printf("Parent linked to datapool of tank 3 at address %p.....\n", mytank3);
	struct tankDataPool 	 *mytank4 = (struct tankDataPool *)(tank4.LinkDataPool());
	printf("Parent linked to datapool of tank 4 at address %p.....\n", mytank4);
	*/



	return 0;
}
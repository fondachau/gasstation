//Fonda Chau 15954143
#include <stdio.h>
#include "..\PumpDataPool.h"
#include "..\rt.h"
#include "Pumps.h"


int main() {

	Pump PumpProcess1(pump1data,1,1,1);
	Pump PumpProcess2(pump2data, 2, 1, 1);// , Pump2("Pump2"), Pump3("Pump3"), Pump4("Pump4");
	Pump PumpProcess3(pump3data,3,1,1);// , Pump2("Pump2"), Pump3("Pump3"), Pump4("Pump4");
	Pump PumpProcess4(pump4data,4,1,1);// , Pump2("Pump2"), Pump3("Pump3"), Pump4("Pump4");

	PumpProcess1.Resume();
	PumpProcess2.Resume();
	PumpProcess3.Resume();
	PumpProcess4.Resume();



getchar();

return 0;
}
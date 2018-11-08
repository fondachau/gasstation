#include<stdio.h>
#include "..\Customer.h"



int main() {




	char bob[10] = "bob      ";
	char tim[10] = "tim      ";
	char john[10] = "john     ";
	char steve[10] = "steve    ";
	char phil[10] = "Phil     ";
	char Dan[10] = "Dan      ";
	char Chuck[10] = "Chuck    ";
	
	Customer customerbob(10123321, bob, 78, 1,35.0);
	customerbob.Resume();
	SLEEP(100);
	/**/
	Customer customertim(21234123, tim, 91, 2,45.0);
	customertim.Resume();
	
	SLEEP(100);
	Customer customerjohn(38765432, john, 91, 3,30.0);
	customerjohn.Resume();
	
	SLEEP(100);
	Customer customersteve(41827364, steve, 80, 4,20.0);
	customersteve.Resume();
	
	SLEEP(100);
	
	Customer customerphil(53234123, phil, 78, 1, 25.0);
	customerphil.Resume();
	SLEEP(100); 

	Customer customerdan(65234123, Dan, 97, 1, 30.0);
	customerdan.Resume();
	SLEEP(1000);

	Customer customerchuck(73234123, Chuck, 91, 1, 45.0);
	customerchuck.Resume();


	char cust[10] = "customer ";
	Customer *thePassengers[100];
	for (int i = 0; i < 100; i++) {
		int Nameindex = rand() % 4;
		int gradeindex = rand() % 4;
		int gradedesired;
		if (gradeindex == 0) {
			gradedesired = 78;
		}
		else if (gradeindex == 1) {
			gradedesired = 80;
		}
		else if (gradeindex == 2) {
			gradedesired = 91;
		}
		else {
			gradedesired = 97;
		}
		int pumpindex = (rand() % 4) + 1;
		int desiredVolumeindex = ((rand() % 10)+1) * 5;
		thePassengers[i] = new Customer(i, cust, gradedesired, pumpindex, desiredVolumeindex);
		thePassengers[i]->Resume();
		Sleep(rand() % 1000);
	}
	
	while(1){}
	return 0;
}
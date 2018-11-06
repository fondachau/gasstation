//Fonda Chau 15954143

#pragma once
#include 	<stdio.h>
//char pump1data[] = "Pump1";

char pump1data[] = "Pump1";
char pump2data[] = "Pump2";
char pump3data[] = "Pump3";
char pump4data[] = "Pump4";

struct 	    PumpDataPool {		
	int pumpnumber;
	int creditcard;
	char name[10];
	int status;
	int tankusing;
	double volume;
};


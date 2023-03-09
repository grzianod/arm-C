#include <stdio.h>
#include "led/led.h"

#define CHARACTERS 1520
volatile char _table[CHARACTERS];


void compute_table() {
//simil-hash function --> letter A : ASCIIcode '65', MORSEcode '01', HASHcode sum(ASCIImorse*2^pos)	
_table[145] = 65; 
_table[728] = 66; 
_table[730] = 67;
_table[340] = 68; 
_table[48] = 69; 
_table[722] = 70; 
_table[342] = 71;
_table[720] = 72;								
_table[144] = 73;
_table[727] = 74;
_table[341] = 75;
_table[724] = 76;
_table[147] = 77;
_table[146] = 78;
_table[343] = 79;
_table[726] = 80;
_table[733] = 81;
_table[338] = 82;
_table[336] = 83;
_table[49] = 84;
_table[337] = 85;
_table[721] = 86;
_table[339] = 87;
_table[729] = 88;
_table[731] = 89;
_table[732] = 90;
_table[1519] = 48;
_table[1503] = 49;
_table[1495] = 50;
_table[1491] = 51;
_table[1489] = 52;
_table[1488] = 53;
_table[1504] = 54;
_table[1512] = 55;
_table[1516] = 56;
_table[1518] = 57;
	
}


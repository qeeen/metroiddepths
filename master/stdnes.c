#include "stdnes.h"

int getbit(byte dat, int bit){
	return (dat >> bit)%2;
}

int* get_bits(int n, int bitswanted){
	int* bits = malloc(sizeof(int) * bitswanted);  
	int k;
	for(k=0; k<bitswanted; k++){
		int mask =  1 << k;
		int masked_n = n & mask;
		int thebit = masked_n >> k;
		bits[k] = thebit;
	}
	return bits; 
}


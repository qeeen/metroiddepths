#include "cart.h"
#include "stdnes.h"
#include "tiles.h"
#include <stdio.h>
#include <stdlib.h>

int inityet = 0;

int* cartmain(int* inputs){
	int *spritebox;//816

	
	if(*(inputs+2)){
		worldx+=1;
	}
	if(*(inputs+1)){
		worldx-=1;
	}
	if(*(inputs+3)){
		worldy-=1;
	}
	if(*(inputs+4)){
		worldy+=1;
	}
	
	if(!inityet){
		test_init();
		inityet = 1;
	}
	spritebox = grab_sprites();

	return spritebox;
}

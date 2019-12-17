#include "load.h"
#include "cart.h"
#include "stdnes.h"
#include "tiles.h"
#include <stdio.h>
#include <stdlib.h>

int cart_init(int* spritesheet, int* palettes){

	spritesheet = get_pixels();

	*(palettes + 0) = 0x671F;
	*(palettes + 1) = 0x03FF;
	*(palettes + 2) = 0x7FFF;
	*(palettes + 3) = 0x0000;

	set_tile(0, spritesheet + 32, palettes);
	set_tile(1, spritesheet + 16, palettes);

//	printf("%d, %d, %d, %d\n", *(spritesheet + 0), *(spritesheet + 1), *(spritesheet + 2), *(spritesheet + 3));

	test_init();
	return 0;
}

int* cartmain(int* spritesheet, int* palettes, int* inputs){
	int *spritebox;//816

	int dbug_cam_spd = 1;

	if(*(inputs+2)){
		worldx += dbug_cam_spd;
	}
	if(*(inputs+1)){
		worldx -= dbug_cam_spd;
	}
	if(*(inputs+3)){
		worldy -= dbug_cam_spd;
	}
	if(*(inputs+4)){
		worldy += dbug_cam_spd;
	}
	
	spritebox = grab_sprites();

	return spritebox;
}

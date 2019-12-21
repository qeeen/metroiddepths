#include "cart.h"
#include "load.h"
#include "stdnes.h"
#include "tiles.h"
#include <stdio.h>
#include <stdlib.h>

dyna* testsprite = NULL;

int cart_init(int* spritesheet, int* palettes){
	spritesheet = get_pixels();

	*(palettes + 0) = 0x671F;
	*(palettes + 1) = 0x03FF;
	*(palettes + 2) = 0x7FFF;
	*(palettes + 3) = 0x0000;

	set_tile(0, spritesheet + 32, palettes);
	set_tile(1, spritesheet + 16, palettes);

	testsprite = malloc(sizeof(dyna));
	testsprite->x = 128;
	testsprite->y = 128;
	testsprite->img = spritesheet+16;
	testsprite->pal = palettes;

	dynaarr[0] = testsprite;

	test_init();
	return 0;
}

int* cartmain(int* spritesheet, int* palettes, int* inputs){
	int *spritebox;//818

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

	//this code needs to be moved, realloc is slow
	*(spritebox + 1) = 1;
	spritebox = realloc(spritebox, sizeof(int)*(*(spritebox + 0)*3 + *(spritebox + 1)*3 + 2));
	*(spritebox + *(spritebox+0)*3 + 2 + 0) = testsprite->x;
	*(spritebox + *(spritebox+0)*3 + 2 + 1) = testsprite->y;
	*(spritebox + *(spritebox+0)*3 + 2 + 2) = 0;

	return spritebox;
}

#include "cart.h"

dyna* testsprite = NULL;//for debug purposes
int dyna_p = -1;

void set_palette(int* pal_list, int pal, int color0, int color1, int color2, int color3){
	*(pal_list + (pal*4) + 0) = color0;
	*(pal_list + (pal*4) + 1) = color1;
	*(pal_list + (pal*4) + 2) = color2;
	*(pal_list + (pal*4) + 3) = color3;
}

dyna* create_dyna(int* spritesheet, int* palettes, int x, int y, int imgx, int imgy, int pal_loc){
	dyna* new_dyna = malloc(sizeof(dyna));
	new_dyna->x = x;
	new_dyna->y = y;
	new_dyna->img = spritesheet + imgx + imgy*SPRITESHEET_DIM;
	new_dyna->pal = palettes + PALETTE_SIZE*pal_loc;

	dyna_p++;
	if(dyna_p >= DYNA_MAX){
		return NULL;
	}
	dynaarr[dyna_p] = new_dyna;
	return new_dyna;
}

int cart_init(int* spritesheet, int* palettes){
	spritesheet = get_pixels();

	set_palette(palettes, 0, 0x671F, 0x03FF, 0x7FFF, 0x000);

	set_tile(0, spritesheet + 32, palettes);
	set_tile(1, spritesheet + 16, palettes);

	testsprite = create_dyna(spritesheet, palettes, 128, 128, 16, 0, 0);

	dynaarr[0] = testsprite;

	test_init();
	return 0;
}

//important to note, this is run on loop
int* cart_main(int* spritesheet, int* palettes, int* inputs){
	int *spritebox;//818

	int dbug_cam_spd = 1;

	if(*(inputs+2)){
		shift_screen_right(dbug_cam_spd);
	}
	if(*(inputs+1)){
		shift_screen_left(dbug_cam_spd);
	}
	if(*(inputs+3)){
		shift_screen_up(dbug_cam_spd);
	}
	if(*(inputs+4)){
		shift_screen_down(dbug_cam_spd);
	}
	
	spritebox = grab_sprites();

	//this code needs to be moved/changed, realloc is slow
	*(spritebox + 1) = 1;
	spritebox = realloc(spritebox, sizeof(int)*(*(spritebox + 0)*3 + *(spritebox + 1)*3 + 2));
	*(spritebox + *(spritebox+0)*3 + 2 + 0) = testsprite->x;
	*(spritebox + *(spritebox+0)*3 + 2 + 1) = testsprite->y;
	*(spritebox + *(spritebox+0)*3 + 2 + 2) = 0;

	return spritebox;
}

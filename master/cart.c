#include "cart.h"

int dyna_p = -1;

void set_palette(int* pal_list, int pal, int color0, int color1, int color2, int color3){
	*(pal_list + (pal*PALETTE_SIZE) + 0) = color0;
	*(pal_list + (pal*PALETTE_SIZE) + 1) = color1;
	*(pal_list + (pal*PALETTE_SIZE) + 2) = color2;
	*(pal_list + (pal*PALETTE_SIZE) + 3) = color3;
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

	set_palette(palettes, 0, cx02, cx11, cx21, cx0D);
	set_palette(palettes, 1, cx15, cx25, cx1B, cx0D);

	set_tile(0, spritesheet + 0, palettes);
	set_tile(1, spritesheet + 16, palettes);

	dyna* testsprite  = create_dyna(spritesheet, palettes, 128, 128, 0, 0, 1);
	dyna* testsprite2 = create_dyna(spritesheet, palettes, 128, 160, 32, 0, 1);
	dyna* testsprite3 = create_dyna(spritesheet, palettes, 128, 220, 48, 0, 1);

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
	*(spritebox + 1) = dyna_p+1;
	spritebox = realloc(spritebox, sizeof(int)*(*(spritebox + 0)*3 + *(spritebox + 1)*3 + 2));
	for(int i = 0; i < dyna_p+1; i++){
		dyna* current = *(dynaarr+i);
		*(spritebox + 2 + *(spritebox+0)*3 + i*3 + 0) = current -> x;
		*(spritebox + 2 + *(spritebox+0)*3 + i*3 + 1) = current -> y;
		*(spritebox + 2 + *(spritebox+0)*3 + i*3 + 2) = i;
	}

	return spritebox;
}

#include "cart.h"

int dyna_p = -1;
dyna* player_sprite[8];//main dynamic sprite for the player
body* player;

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
	set_palette(palettes, 1, cx15, cx34, cx07, cx0D);

	set_tile(0, spritesheet + 0, palettes);
	set_tile(1, spritesheet + 1*16, palettes);

	//should get put into a function to automate
	player_sprite[0] = create_dyna(spritesheet, palettes, 128, 128, 11*16 + 0*8, 0, 1);
	player_sprite[1] = create_dyna(spritesheet, palettes, 136, 128, 11*16 + 1*8, 0, 1);
	player_sprite[2] = create_dyna(spritesheet, palettes, 128, 136, 11*16 + 2*8, 0, 1);
	player_sprite[3] = create_dyna(spritesheet, palettes, 136, 136, 11*16 + 3*8, 0, 1);
	player_sprite[4] = create_dyna(spritesheet, palettes, 128, 144, 11*16 + 4*8, 0, 1);
	player_sprite[5] = create_dyna(spritesheet, palettes, 136, 144, 11*16 + 5*8, 0, 1);
	player_sprite[6] = create_dyna(spritesheet, palettes, 128, 152, 11*16 + 6*8, 0, 1);
	player_sprite[7] = create_dyna(spritesheet, palettes, 136, 152, 11*16 + 7*8, 0, 1);

	player = malloc(sizeof(body));
	player->sprites = player_sprite;
	player->sprite_count = 8;
	player->x = 128;
	player->y = 128;

	test_init();
	return 0;
}

//important to note, this is run on loop
int* cart_main(int* spritesheet, int* palettes, int* inputs){
	int *spritebox;//818

	int dbug_cam_spd = 2;
	xspd_in(player, dbug_cam_spd, *(inputs+1), *(inputs+2));
	auto_body(player);
	
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

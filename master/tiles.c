#include "globals.h"
#include "tiles.h"
#include <stdlib.h>
#include <stdio.h>

unsigned char chunks[CHUNK_COUNT * (SCREEN_WIDTH/16)*(SCREEN_HEIGHT/16)];
unsigned char* map[MAP_DIM * MAP_DIM];

int worldx = 0;
int worldy = 0;

int* grab_sprites(){
	//world limits, needs to be moved somewhere more appropriate later
	if(worldx < 0) {worldx = 0;}
	if(worldy < 0) {worldy = 0;}
	

	int *sprites = malloc(816 * sizeof(int));
	
	int worldx_offset = worldx%16;
	int worldy_offset = worldy%16;


	for(int y = 0; y < 16; y++){
		for(int x = 0; x < 17; x++){
			int tilex = 16*x - worldx_offset;
			int tiley = 16*y - worldy_offset;
			sprites[(x+(y*17))*3] = tilex;
			sprites[((x+(y*17))*3) + 1] = tiley;
			sprites[((x+(y*17))*3) + 2] = grab_tile(worldx+x*16, worldy+y*16);
		}
	}

	return sprites;
}

int is_solid(int xpos, int ypos){
	return 0;
}

unsigned char grab_tile(int xpos, int ypos){
	int cxpos = (int)(xpos/SCREEN_WIDTH);
	int cypos = (int)(ypos/SCREEN_HEIGHT);
	int rxpos = (xpos%SCREEN_WIDTH)/16;
	int rypos = (ypos%SCREEN_HEIGHT)/16;

	unsigned char *chunk = map[cxpos + 64*cypos];
	unsigned char tile = *(chunk + rxpos + 16*rypos);
	return tile;
}

unsigned char* grab_tile_ptr(int xpos, int ypos){	
	return NULL;
}

void set_tile(int tilenum, int* img, int* pal){
	loaded_tiles[tilenum*2] = img;
	loaded_tiles[tilenum*2 + 1] = pal;
}

void test_init(){
	for(int i = 0; i < 240; i++){
		chunks[i] = 1;
	}
	for(int i = 0; i < 240; i++){
		chunks[240+i] = 0;
	}
	for(int i = 0; i < 4096; i++){
		map[i] = ((i + i/64) % 2) ? chunks : chunks + 240;
	}
}

void shift_screen_left(){
	worldx++;
}

void shift_screen_right(){
	worldx--;
}

void shift_screen_up(){
	worldy--;
}

void shift_screen_down(){
	worldx++;
}



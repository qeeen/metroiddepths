#include "tiles.h"
#include <stdlib.h>
#include <stdio.h>

unsigned char chunks[7680];
unsigned char* map[4096];

int worldx = 144;
int worldy = 0;

int* grab_sprites(){
	int *sprites = malloc(816 * sizeof(int));
	
	int worldx_offset = worldx%16;
	int worldy_offset = worldy%16;

	for(int y = 0; y < 16; y++){
		for(int x = 0; x < 17; x++){
			int tilex = x*16 - worldx_offset;
			int tiley = y*16 - worldy_offset;
			sprites[(x+(y*17))*3] = tilex;
			sprites[((x+(y*17))*3) + 1] = tiley;
			sprites[((x+(y*17))*3) + 2] = (int)grab_tile(worldx+x*16, (worldy+y)*17*16);
		}
	}

	return sprites;
}

int is_solid(int xpos, int ypos){
	int cxpos = xpos/256;
	int cypos = ypos/240;
	int rxpos = xpos%256;
	int rypos = ypos%240;

	unsigned char *chunk = map[cxpos + 64*cypos];
	unsigned char tile = chunk[rxpos + 16*rypos];
	return (tile & 0x80 != 0) ? 1 : 0;
}

unsigned char grab_tile(int xpos, int ypos){	
	int cxpos = xpos/256;
	int cypos = ypos/240;
	int rxpos = xpos%256;
	int rypos = ypos%240;

	unsigned char *chunk = map[cxpos + 64*cypos];
	unsigned char tile = chunk[rxpos + 16*rypos];
	return tile;
}

unsigned char* grab_tile_ptr(int xpos, int ypos){	
	int cxpos = xpos/256;
	int cypos = ypos/240;
	int rxpos = xpos%256;
	int rypos = ypos%240;

	unsigned char *chunk = map[cxpos + 64*cypos];
	unsigned char *tile = chunk + (rxpos + 16*rypos);
	return tile;
}

void test_init(){
	for(int i = 0; i < 240; i++){
		chunks[i] = 1;
	}
	for(int i = 0; i < 240; i++){
		chunks[240+i] = 0;
	}
	for(int i = 0; i < 4096; i++){
		map[i] = (i % 2) ? chunks : chunks + 240;
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



#include "tiles.h"

int worldx = 0;
int worldy = 0;

int* grab_sprites(){
	int *sprites = malloc(818 * sizeof(int));
	
	int worldx_offset = worldx%16;
	int worldy_offset = worldy%16;

	sprites[0] = 272;

	for(int y = 0; y < 16; y++){
		for(int x = 0; x < 17; x++){
			int tilex = 16*x - worldx_offset;
			int tiley = 16*y - worldy_offset;
			sprites[(x+(y*17))*3 + 2] = tilex;
			sprites[((x+(y*17))*3) + 1 + 2] = tiley;
			sprites[((x+(y*17))*3) + 2 + 2] = grab_tile(worldx+x*16, worldy+y*16);
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

void shift_screen_left(int amount){
	worldx -= amount;
	if(worldx > MAP_DIM*SCREEN_WIDTH) {worldx = MAP_DIM*SCREEN_WIDTH;}
}

void shift_screen_right(int amount){
	worldx += amount;
	if(worldx < 0) {worldx = 0;}
}

void shift_screen_up(int amount){
	worldy -= amount;
	if(worldy < 0) {worldy = 0;}
}

void shift_screen_down(int amount){
	worldy += amount;
	if(worldy > MAP_DIM*SCREEN_HEIGHT) {worldy = MAP_DIM*SCREEN_HEIGHT;}
}



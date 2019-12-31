#include "tiles.h"

int worldx = 0;
int worldy = 0;
int layer_size = CHUNK_COUNT * (SCREEN_WIDTH/16)*(SCREEN_HEIGHT/16);

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
			//printf("%d", grab_tile(worldx+x*16, worldy+y*16));
		}
		//printf("\n");
	}

	return sprites;
}

int is_solid(int xpos, int ypos){
	unsigned char layer = grab_layer(xpos, ypos);
	if(layer == 2){
		return 1;
	}
	return 0;
}

unsigned char grab_layer(int xpos, int ypos){
	int cxpos = (int)(xpos/SCREEN_WIDTH);
	int cypos = (int)(ypos/SCREEN_HEIGHT);
	int rxpos = (xpos%SCREEN_WIDTH)/16;
	int rypos = (ypos%SCREEN_HEIGHT)/16;

	unsigned char *chunk = map[cxpos + 64*cypos];
	unsigned char layer = *(chunk + rxpos + 16*rypos);
	
	return layer;
}

unsigned char grab_tile(int xpos, int ypos){
	int cxpos = (int)(xpos/SCREEN_WIDTH);
	int cypos = (int)(ypos/SCREEN_HEIGHT);
	int rxpos = (xpos%SCREEN_WIDTH)/16;
	int rypos = (ypos%SCREEN_HEIGHT)/16;

	unsigned char *chunk = map[cxpos + 64*cypos];
	unsigned char layer = *(chunk + rxpos + 16*rypos);
	unsigned char tile = *(chunk + layer_size*layer + rxpos + 16*rypos);

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
		chunks[240+i] = 1;
	}
	for(int i = 0; i < 32; i++){
		chunks[240+16*13 + i] = 2;
	}

	for(int i = 0; i < 32; i++){
		chunks[layer_size*2 + 240+16*13 + i] = 1;
	}

	for(int i = 0; i < 4096; i++){
		map[i] = ((i + i/64) % 2) ? chunks : chunks + 240;
	}
}

void world_init(int* map_data, int room_count){
	for(int i = 0; i < 240; i++){
		chunks[i] = 1;
	}
	for(int c = 1; c < room_count+1; c++){
		for(int i = 0; i < 240; i++){
			int layer = (map_data[(c-1)*240 + i] == 0) ? 1 : 2;
			chunks[c*240 + i] = layer;
			chunks[layer_size*layer + c*240 + i] = map_data[240*(c-1) + i];
		}
	}
	map[0] = chunks + 240 * 1;
	map[1] = chunks + 240 * 2;
	map[2] = chunks + 240 * 3;
	for(int i = 3; i < 4096; i++){
		map[i] = chunks;
	}
}

void shift_screen_left(int amount){
	worldx -= amount*2;
	if(worldx < 0) {worldx = 0;}
}

void shift_screen_right(int amount){
	worldx += amount*2;
	if(worldx > MAP_DIM*SCREEN_WIDTH) {worldx = MAP_DIM*SCREEN_WIDTH;}
}

void shift_screen_up(int amount){
	worldy -= amount;
	if(worldy < 0) {worldy = 0;}
}

void shift_screen_down(int amount){
	worldy += amount;
	if(worldy > MAP_DIM*SCREEN_HEIGHT) {worldy = MAP_DIM*SCREEN_HEIGHT;}
}



#ifndef TILES_H
#define TILES_H

/// HEADERS ///
#include "globals.h"
#include "stdnes.h"

#include <stdlib.h>
#include <stdio.h>

/// FUNCTIONS ///
void test_init(void);//debug world initialization
void world_init(int* map_data, int room_count);//actual world initialization

//tile getters//
int* grab_sprites();//get all tile images into an array(needs to be freed)
int is_solid(int xpos, int ypos);//unfinished
unsigned char grab_layer(int xpos, int ypos);
unsigned char grab_tile(int xpos, int ypos);
unsigned char* grab_tile_ptr(int xpos, int ypos);//unfinished

//world modifiers//
void shift_screen_left(int amount);
void shift_screen_right(int amount);
void shift_screen_up(int amount);
void shift_screen_down(int amount);

void set_tile(int tilenum, int* img, int* pal);//changes a loaded tile, not a specific tile on the map


/// VARIABLES ///
int* loaded_tiles[TILE_MAX*2];//2*32 array of image/palette data for tiles that are "loaded into memory"

//world data//
unsigned char chunks[CHUNK_COUNT*4 * (SCREEN_WIDTH/16)*(SCREEN_HEIGHT/16)];
//4 layers
//layer 0, shows what layer the tile is on
//layer 1, background layer
//layer 2, solid tiles
//layer 3, dynamic tiles

int layer_size;

unsigned char* map[MAP_DIM * MAP_DIM];

int worldx;
int worldy;

#endif

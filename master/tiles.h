#ifndef TILES_H
#define TILES_H

//unsigned char chunks[7680]; 32 16*15 chunks, msb is solidity
//unsigned char* map[4096]; 64*64 pointers to chunks

int worldx;
int worldy;

int* loaded_tiles[64];

int* grab_sprites();

void shift_screen_left(void);
void shift_screen_right(void);
void shift_screen_up(void);
void shift_screen_down(void);

void set_tile(int tilenum, int* img, int* pal);

int is_solid(int xpos, int ypos);

unsigned char grab_tile(int xpos, int ypos);
unsigned char* grab_tile_ptr(int xpos, int ypos);

void test_init(void);

#endif

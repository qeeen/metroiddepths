#include "globals.h"
#include "draw.h"
#include "stdnes.h"
#include "cart.h"
#include "tiles.h"
#include <stdlib.h>
#include <stdio.h>

int gamescreen[SCREEN_WIDTH * SCREEN_HEIGHT];
int* spritesheet;//[SPRITESHEET_DIM*SPRITESHEET_DIM * SPRITE_DIM*SPRITE_DIM] 64*64 grid of 8*8 sprites
int palettes[PALETTE_COUNT * PALETTE_SIZE];//16 4 color palettes

void update_gamescreen(int* sprite_list){
	for(int i = 0; i < SCREEN_WIDTH*SCREEN_HEIGHT; i++){
		gamescreen[i] = 0x0000;
	}
	sprite_list+=2;//remove this when stuff works

	for(int i = 0; i < 816; i+=3){
		int x = *(sprite_list+i);
		int y = *(sprite_list+i+1);
		int tile = *(sprite_list+i+2);

		for(int r = 0; r < 16; r++){
			if(y+r < 0 || y+r > SCREEN_HEIGHT-1){
				continue;
			}

			for(int c = 0; c < 16; c++){
				if(x+c < 0 || x+c > SCREEN_WIDTH-1){
					continue;
				} else {
					int palsel = *(loaded_tiles[tile*2] + c + r*512);
					gamescreen[x+c + (y+r)*SCREEN_WIDTH] = *(palettes + palsel);
				}
			}
		}
	}
}

int main(int argc, char *argv[]){
	draw_init();
	int* inputs;
	int* spritebox;

	cart_init(spritesheet, palettes);//user defined init
	while(1){
		inputs = handle_input();
		if(inputs[0] == 1){
			break;
		}
		spritebox = cartmain(spritesheet, palettes, inputs);
		update_gamescreen(spritebox);
		draw_loop(gamescreen);
		free(spritebox);
	}
	free(spritesheet);
	draw_destruct();
	return 0;
}

#include "draw.h"
#include "cart.h"
#include "tiles.h"
#include "dyna.h"
#include "globals.h"
#include "stdnes.h"

#include <stdlib.h>
#include <stdio.h>

int gamescreen[SCREEN_WIDTH * SCREEN_HEIGHT];
int* spritesheet;//[SPRITESHEET_DIM*SPRITESHEET_DIM * SPRITE_DIM*SPRITE_DIM] 64*64 grid of 8*8 sprites
int palettes[PALETTE_COUNT * PALETTE_SIZE];//16*4 color palettes

void update_gamescreen(int* sprite_list){
	for(int i = 0; i < SCREEN_WIDTH*SCREEN_HEIGHT; i++){
		gamescreen[i] = 0x0000;
	}

	int tile_count = sprite_list[0];
	int dyna_count = sprite_list[1];
	sprite_list+=2;//remove this when stuff works

	for(int i = 0; i < tile_count*3; i+=3){
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
					int palsel = *(loaded_tiles[tile*2] + c + r*512);//value, 1-4 for each pixel
					int* pal = loaded_tiles[tile*2+1];
					gamescreen[x+c + (y+r)*SCREEN_WIDTH] = *(pal + palsel);
				}
			}
		}
	}

	sprite_list += tile_count*3;
	
	for(int i = 0; i < dyna_count*3; i+=3){
		int x = *(sprite_list+i);
		int y = *(sprite_list+i+1);
		dyna* cur_dyna = dynaarr[*(sprite_list+i+2)];

		for(int r = 0; r < 8; r++){
			if(y+r < 0 || y+r > SCREEN_HEIGHT-1){
				continue;
			}

			for(int c = 0; c < 8; c++){
				if(x+c < 0 || x+c > SCREEN_WIDTH-1){
					continue;
				} else {
					int palsel = *(cur_dyna->img + c + r*512);
					if(palsel == 3){
						continue;
					}
					int* pal = cur_dyna->pal;
					gamescreen[x+c + (y+r)*SCREEN_WIDTH] = *(pal + palsel);
				}
			}
		}
		
	}
}

int main(int argc, char* argv[]){
	draw_init();
	int* inputs;
	int* spritebox;

	cart_init(spritesheet, palettes);//user defined init
	while(1){
		inputs = handle_input();
		if(inputs[0] == 1){
			break;
		}
		spritebox = cart_main(spritesheet, palettes, inputs);
		update_gamescreen(spritebox);
		draw_loop(gamescreen);
		free(spritebox);
	}
	free(spritesheet);
	draw_destruct();
	return 0;
}

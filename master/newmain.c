#include "draw.h"
#include "stdnes.h"
#include "cart.h"
#include "tiles.h"
#include <stdlib.h>
#include <stdio.h>

int gameScreen[256 * 240];

void update_gamescreen(int* sprite_list){
	for(int i = 0; i < 256*240; i++){
		gameScreen[i] = 0x0000;
	}


	for(int i = 0; i < 816; i+=3){
		int x = *(sprite_list+i);
		int y = *(sprite_list+i+1);
		int tile = *(sprite_list+i+2);

		for(int r = 0; r < 16; r++){
			if(y+r < 0 || y+r > 239){
				continue;
			}

			for(int c = 0; c < 16; c++){
				if(x+c < 0 || x+c > 255){
					continue;
				} else if(tile == 1){
					gameScreen[x+c + (y+r)*256] = 0x311F;
				} else {
					gameScreen[x+c + (y+r)*256] = 0x33E8;
				}
			}
		}
	}
}

int main(int argc, char *argv[]){
	draw_init();
	int* inputflags;
	int* spritebox;

	cart_init();//user defined init
	while(1){
		inputflags = handle_input();
		if(inputflags[0] == 1){
			break;
		}
		spritebox = cartmain(inputflags);//user defined main (takes array of inputs, spits out array of spritedata)
		update_gamescreen(spritebox);
		draw_loop(gameScreen);
		free(spritebox);
	}
	draw_destruct();
	return 0;
}

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
		if(tile == 1){
			printf("%d\n%d\n\n", x, y);
		}
		for(int r = 0; r < 16; r++){
			if(y + r < 0){
				continue;
			}
			for(int c = 0; c < 16; c++){
				if(tile == 1){
					if(x+c < 0){
						continue;
					}
					gameScreen[x+c + (y+r)*256] = 0x311F;
				} else {
					//gameScreen[x+c + (y+r)*256] = 0x33E8;
				}
			}
		}
	}
	/*
	for(int i = 0; i < 240; i++){
		for(int k = 0; k < 256; k++){
			printf("%d ", gameScreen[i*256 + k]);
		}
		printf("\n");
	}
	*/
}

int main(void){
	draw_init();
	int* inputflags;
	int* spritebox;

	while(1){
		inputflags = handle_input();
		if(inputflags[0] == 1){
			break;
		}
		spritebox = cartmain(inputflags);
		/*
		for(int i = 0; i < 816; i++){
			printf("%d\n", *(spritebox + i));
		}
		*/
		update_gamescreen(spritebox);
		draw_loop(gameScreen);
		free(spritebox);
		//break;
	}
	draw_destruct();
	return 0;
}

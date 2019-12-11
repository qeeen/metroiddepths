#include "draw.h"
#include "stdnes.h"
#include "cart.h"
#include <stdlib.h>
#include <stdio.h>

int gameScreen[256 * 240];

void update_gamescreen(int* sprite_list){
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
		
		for(int i = 0; i < 816; i++){
			printf("%d\n", *(spritebox + i));
		}
		
		update_gamescreen(spritebox);
		draw_loop(gameScreen);
		free(spritebox);
		break;
	}
	draw_destruct();
	return 0;
}

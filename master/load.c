#include "load.h"
#include <stdlib.h>

int* get_pixels(){
	int sheet_size = SPRITESHEET_DIM*SPRITESHEET_DIM * SPRITE_DIM*SPRITE_DIM;
	IMG_Init(IMG_INIT_PNG);
	
	SDL_Surface* sheet = IMG_Load("spritesheet.png");
	unsigned char* pixels = (unsigned char*)sheet->pixels;
	
	int* greyscale = malloc(sizeof(int)* sheet_size);
	for(int i = 0; i < sheet_size; i+=4){
		unsigned char r = *(pixels + i + 0);
		unsigned char g = *(pixels + i + 1);
		unsigned char b = *(pixels + i + 2);
		unsigned char a = *(pixels + i + 3);
		
		if(r == 255){
			*(greyscale + i/4) = 0;
		}
		if(g == 255){
			*(greyscale + i/4) = 1;
		}
		if(b == 255){
			*(greyscale + i/4) = 2;
		}
		if(a == 0){
			*(greyscale + i/4) = 3;
		}
	}

	SDL_FreeSurface(sheet);
	IMG_Quit();
	return greyscale;
}


#include "load.h"

int* get_pixels(){
	int sheet_size = SPRITESHEET_DIM*SPRITESHEET_DIM * SPRITE_DIM*SPRITE_DIM;
	IMG_Init(IMG_INIT_PNG);
	
	SDL_Surface* sheet = IMG_Load("spritesheet.png");
	unsigned char* pixels = (unsigned char*)sheet->pixels;
	
	int* greyscale = malloc(sizeof(int) * sheet_size);
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

int* get_map(void){
	FILE* map_file = fopen("output.out", "r");

	fseek(map_file, 0, SEEK_END);
	int size = (int)ftell(map_file);
	rewind(map_file);

	int* map_data = malloc(sizeof(int)*size + 1);
	int index = 0;
	int current_value;
	while((current_value = fgetc(map_file)) != EOF){
		if((char)current_value != '\n'){
			map_data[index] = current_value-33;
			index++;
		}
	}
	fclose(map_file);
	return map_data;
}

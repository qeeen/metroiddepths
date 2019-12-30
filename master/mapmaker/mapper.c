#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* get_string_form(SDL_Surface** images, int image_count);

int main(int argc, char** argv){
	if(argc == 1){
		printf("Error: File count not given\n");
		return -1;
	}
	int room_count = atoi(argv[1]);
	if(room_count > 99){
		printf("Error File count too high\n");
		return -1;
	}
	int initted = IMG_Init(IMG_INIT_PNG);
	if(initted&IMG_INIT_PNG != IMG_INIT_PNG){
		printf("SDL2_image png init failed\n");
		return -1;
	}
	SDL_Surface* images[room_count];

	for(int i = 0; i < room_count; i++){
		char name[] = "room00.png";
		name[5] = (char)(i%10)+48;
		name[4] = (char)(i/10)+48;
		images[i] = IMG_Load(name);
		printf(name);
		printf("\n");
	}
	char* room_data = get_string_form(images, room_count);
	FILE* output = fopen("output.out", "w+");
	fprintf(output, room_data);

	fclose(output);
}

char* get_string_form(SDL_Surface** images, int image_count){
	unsigned char* string_form = malloc((sizeof(char) * 16*15 + 1) * image_count);
	for(int i = 0; i < image_count; i++){	
		SDL_Surface* current = images[i];
		unsigned char* pixels = (unsigned char*)current->pixels;
		for(int k = 0; k < 240; k++){
			unsigned char r = *(pixels + k*4 + 0);
			unsigned char g = *(pixels + k*4 + 1);
			unsigned char b = *(pixels + k*4 + 2);
			unsigned char a = *(pixels + k*4 + 3);

			if(a == 0){
				string_form[(i*241) + k] = 33 + 0;
				if(k == 239){
					string_form[((i+1)*241 - 1)] = '\n';
				}
				continue;
			}
			int current_pixel = r*65536 + g*256 + b;
			switch(current_pixel){
				case 0x2000B2:
					string_form[i*241 + k] = 33 + 1;
					break;
				case 0x4161FB:
					string_form[i*241 + k] = 33 + 2;
					break;
				case 0x6110A2:
					string_form[i*241 + k] = 33 + 3;
					break;
				case 0x61A2FF:
					string_form[i*241 + k] = 33 + 4;
					break;
				case 0x92D3FF:
					string_form[i*241 + k] = 33 + 5;
					break;
				case 0x794100:
					string_form[i*241 + k] = 33 + 6;
					break;
				case 0xA23000:
					string_form[i*241 + k] = 33 + 7;
					break;
				case 0x495900:
					string_form[i*241 + k] = 33 + 8;
					break;
				case 0x9A2079:
					string_form[i*241 + k] = 33 + 9;
					break;
				case 0xB21030:
					string_form[i*241 + k] = 33 + 10;
					break;
			}
			printf("%d, %d, %d\n", i, k, i*241+k);
		}
		string_form[(i+1)*240 + i] = '\n';
	}
	return string_form;
}

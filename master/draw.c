#include "draw.h"
//#include "entity.h"

/// FUNCTION IMPLEMENTATIONS ///
unsigned int timeleft(){
	unsigned int now;
	
	now = SDL_GetTicks();
	if(next_time <= now){
		return 0;
	} else {
		return next_time - now;
	}
}

int * byte_color(int color){
	int *bits = get_bits(color, 15);
	int r = (bits[0]*1 + bits[1]*2 + bits[2]*4 + bits[3]*8 + bits[4]*16)*8;
	int g = (bits[5]*1 + bits[6]*2 + bits[7]*4 + bits[8]*8 + bits[9]*16)*8;
	int b = (bits[10]*1 + bits[11]*2 + bits[12]*4 + bits[13]*8 + bits[14]*16)*8;
	free(bits);
	static int rgb[3];
	rgb[0] = r;
	rgb[1] = g;
	rgb[2] = b;
	return rgb;
}

void draw_pixel(int x, int y, int r, int g, int b){
	//int * rgb = byte_color(color);
	SDL_SetRenderDrawColor(renderer, r, g, b, 255);
	SDL_RenderDrawPoint(renderer, x, y);
}

void draw_15bit_pixel(int x, int y, int color){
	int *rgb = byte_color(color);	
	unsigned char* pixels = screenarr->pixels;
	
	*(pixels + x*4 + (y*4)*SCREEN_WIDTH*SCALE) = rgb[0];
	*(pixels + x*4 + (y*4)*SCREEN_WIDTH*SCALE+1) = rgb[1];
	*(pixels + x*4 + (y*4)*SCREEN_WIDTH*SCALE+2) = rgb[2];
	*(pixels + x*4 + (y*4)*SCREEN_WIDTH*SCALE+3) = 255;

	//SDL_SetRenderDrawColor(renderer, rgb[0], rgb[1], rgb[2], 255);
	//SDL_RenderDrawPoint(renderer, x, y);
	//draw_pixel(x, y, rgb[0], rgb[1], rgb[2]);
}

void draw_15bit_pixel_arr(int x, int y, int* rgb){
	unsigned char* pixels = screenarr->pixels;
	
	*(pixels + x*4 + (y*4)*SCREEN_WIDTH*SCALE) = rgb[0];
	*(pixels + x*4 + (y*4)*SCREEN_WIDTH*SCALE+1) = rgb[1];
	*(pixels + x*4 + (y*4)*SCREEN_WIDTH*SCALE+2) = rgb[2];
	*(pixels + x*4 + (y*4)*SCREEN_WIDTH*SCALE+3) = 255;	
}

/*
void draw_sprite(byte x, byte y, byte width, byte height, byte pixels[]){
	for(int i = 0; i < height; i++){
		for(int k = 0; k < width; k++){
			draw_pixel(x+k, y+i, pixels[i*width+k]);
		}
	}
}
*/

void draw_init(){
	SDL_Init(SDL_INIT_VIDEO);
	//IMG_Init(IMG_INIT_PNG);

	window = SDL_CreateWindow("gaem",
		SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH*SCALE, SCREEN_HEIGHT*SCALE, 0);
	
	renderer = SDL_CreateRenderer(window, -1, 0);
	//screenarr = SDL_GetWindowSurface(window);
	screenarr = SDL_CreateRGBSurface(0, SCREEN_WIDTH*SCALE, SCREEN_HEIGHT*SCALE, 32, 0, 0, 0, 0);
}

int* handle_input(){
	static int flags[9] = {0, 0, 0, 0, 0, 0, 0, 0, 0};
	while(SDL_PollEvent(&event)){
		switch(event.type){
			case SDL_QUIT:
				flags[0] = 1;
				break;
			case SDL_KEYDOWN:
				switch(event.key.keysym.sym){
					case SDLK_LEFT:
						flags[1] = 1;
						break;
					case SDLK_RIGHT:
						flags[2] = 1;
						break;
					case SDLK_UP:
						flags[3] = 1;
						break;
					case SDLK_DOWN:
						flags[4] = 1;
						break;
					
					case SDLK_LSHIFT:
						flags[5] = 1;
						break;
					case SDLK_LCTRL:
						flags[6] = 1;
						break;
							
					case SDLK_z:
						flags[7] = 1;
						break;
					case SDLK_x:
						flags[8] = 1;
						break;
				}
				break;
			case SDL_KEYUP:
				switch(event.key.keysym.sym){
					case SDLK_LEFT:
						flags[1] = 0;
						break;
					case SDLK_RIGHT:
						flags[2] = 0;
						break;
					case SDLK_UP:
						flags[3] = 0;
						break;
					case SDLK_DOWN:
						flags[4] = 0;
						break;
					
					case SDLK_LSHIFT:
						flags[5] = 0;
						break;
					case SDLK_LCTRL:
						flags[6] = 0;
						break;
							
					case SDLK_z:
						flags[7] = 0;
						break;
					case SDLK_x:
						flags[8] = 0;
						break;
				}
				break;
		}
	}
	return flags;
}

void draw_loop(int *screen){
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderClear(renderer);
	SDL_FillRect(screenarr, NULL, 0);

	SDL_LockSurface(screenarr);

	for(int i = 0; i < SCREEN_HEIGHT; i++){
		for(int k = 0; k < SCREEN_WIDTH; k++){
			int* rgb = byte_color(screen[k + i*SCREEN_WIDTH]);
			if(rgb[0] + rgb[1] + rgb[2] == 0){
				continue;
			}
			for(int px = 0; px < SCALE; px++){
				for(int py = 0; py < SCALE; py++){
					draw_15bit_pixel_arr(k*SCALE+px, i*SCALE+py, rgb);
				}
			}
		}
	}
	SDL_UnlockSurface(screenarr);

	SDL_Texture* tex = SDL_CreateTextureFromSurface(renderer, screenarr);
	SDL_RenderCopy(renderer, tex, NULL, NULL);
	SDL_DestroyTexture(tex);
	SDL_RenderPresent(renderer);

	SDL_Delay(timeleft());
	if(timeleft() == 0){
		next_time = SDL_GetTicks();
	}
	next_time += tick_interval;
}

void draw_destruct(){	
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_FreeSurface(screenarr);

	//IMG_Quit();
	SDL_Quit();
}


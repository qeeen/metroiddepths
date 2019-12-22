#ifndef DRAW_H
#define DRAW_H

/// HEADERS ///
#include "globals.h"
#include "stdnes.h"

#define SDL_MAIN_HANDLED//tells sdl that I have my own main
#include <SDL2/SDL.h>

/// VARIABLES ///

//time keeping//
#define tick_interval 33//33 milliseconds is about 1/30s, to run at 30 fps
static unsigned int next_time;

//window stuff//
SDL_Event event;
SDL_Window* window;
SDL_Renderer* renderer;
SDL_Surface* screenarr;

/// FUNCTIONS ///

//time keeping//
unsigned int time_left(void);

//drawing stuff//
int* byte_color(int color);
void draw_pixel(int x, int y, int r, int g, int b);
void draw_15bitpixel(int x, int y, int color);

//ui control//
void draw_init(void);
int* handle_input(void);
void draw_loop(int* screen);
void draw_destruct(void);

#endif

#ifndef DRAW_H
#define DRAW_H

#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>
#include "globals.h"
#include "stdnes.h"

/// VARIABLES ///

//TIME KEEPING//
#define tick_interval 33
static unsigned int next_time;

//WINDOW STUFF//
SDL_Event event;
SDL_Window * window;
SDL_Renderer * renderer;
SDL_Surface * screenarr;

/// FUNCTIONS ///

//TIME KEEPING//
unsigned int timeLeft(void);

//DRAWING STUFF//
int * byte_color(int color);
void draw_pixel(int x, int y, int r, int g, int b);
void draw_15bitpixel(int x, int y, int color);
//void draw_sprite(byte x, byte y, byte width, byte height, byte pixels[]);

//UI CONTROL//
void draw_init(void);
int* handle_input(void);
void draw_loop(int *screen);
void draw_destruct(void);

#endif

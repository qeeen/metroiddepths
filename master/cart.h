#ifndef CART_H
#define CART_H

/// HEADERS ///
#include "dyna.h"
#include "load.h"
#include "tiles.h"
#include "globals.h"
#include "stdnes.h"

#include <stdio.h>
#include <stdlib.h>

/// FUNCTIONS ///

//state setters//
void set_palette(int* pal_list, int pal, int color0, int color1, int color2, int color3);

dyna* create_dyna(int* spritesheet, int* palettes, int x, int y, int imgx, int imgy, int pal_loc);

//main game processing//
int cart_init(int* spritesheet, int* palettes);//initialize main game processes
int* cart_main(int* spritesheet, int* palettes, int* inputs);//main game loop

/// VARIABLES ///
dyna* dynaarr[DYNA_MAX];//array of currently existing dynamic sprites
int dyna_p;

#endif

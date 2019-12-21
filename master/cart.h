#ifndef CART_H
#define CART_H

#include "dyna.h"

int cart_init(int* spritesheet, int* palettes);
int* cartmain(int* spritesheet, int* palettes, int* inputs);

dyna* dynaarr[1];

#endif

#ifndef IMG_H
#define IMG_H

/// HEADERS ///
#include "globals.h"
#include "stdnes.h"

#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <stdlib.h>

/// FUNCTIONS ///

//returns the spritesheet as a matrix of values from 0-3, for each color on a palette
//3 means transparency on dynamic sprites
int* get_pixels(void);//loads images from "spritesheet.png"

#endif

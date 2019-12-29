#ifndef BODY_H
#define BODY_H

/// HEADERS ///
#include "dyna.h"
#include "tiles.h"
#include "globals.h"
#include "stdnes.h"

#include <stdio.h>
#include <stdlib.h>

/// STRUCTS ///
typedef struct {
	dyna** sprites;
	int sprite_count;
	int x, y;
	int width, height;
	int xspd, yspd;
	int speed;
	int g;
	int termv;

	int state;
	
	int parent;
	int id;
} body;

/// FUNCTIONS ///

//movement stuff/
void move_body(body* b, int xdis, int ydis);
void auto_body(body* b);
void xspd_in(body* b, int speed, int l, int r);

//meta//
void destroy_body(body* b);
#endif

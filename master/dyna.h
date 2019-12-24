#ifndef DYNA_H
#define DYNA_H

/// HEADERS ///
#include "globals.h"
#include "stdnes.h"

/// STRUCTS ///
typedef struct{//dynamic sprite
	int* pal;
	int* img;
	unsigned char x, y;
} dyna;

typedef struct{//group of dynamic sprites
	dyna* parts;
	int size;
} clump; //top left pixel of first dyna is the origin

typedef struct{//group of clumps, for animation
	int cycle, speed, frame_count;
	clump* frames;
} mov_clump;

/// FUNCTIONS ///

//dyna functions//
int overlaps(dyna* from, dyna* to);
int overlaps_bulk(int froml, dyna* from, int tol, dyna* to);
void move_bulk(dyna** list, int c, int xdis, int ydis);

//clump functions//
void move_clump(clump* cl, int xdis, int ydis);
void set_clump_pos(clump* cl, int x, int y);
void set_clump_pal(clump* cl, int* pal);

//moving clump functions//
void animate(mov_clump* anim);

#endif

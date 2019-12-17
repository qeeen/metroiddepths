#ifndef DYNA_H
#define DYNA_H

#include "globals.h"
#include "stdnes.h"

typedef struct{
	int* pal;
	int* img;
	unsigned char x, y;
} dyna;

typedef struct{
	dyna* parts;
	int size;
} clump; //top left pixel of first dyna is the origin

typedef struct{
	int cycle, speed, frame_count;
	clump* frames;
} mov_clump;

int overlaps(dyna* from, dyna* to);
int overlaps_bulk(int froml, dyna* from, int tol, dyna* to);

void move_clump(clump* cl, int xdis, int ydis);
void set_clump_pos(clump* cl, int x, int y);
void set_clump_pal(clump* cl, int* pal);

void animate(mov_clump* anim);

#endif

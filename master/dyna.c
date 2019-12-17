#include "dyna.h"

int overlaps(dyna* from, dyna* to){
	int xover = 0;
	int yover = 0;
	if(to->x >= from->x && to->x+8 <= from->x+8){
		xover = 1;
	}
	if(to->y >= from->y && to->y+8 <= from->y+8){
		yover = 1;
	}

	if(from->x >= to->x && from->x+8 <= to->x+8){
		xover = 1;
	}
	if(from->y >= to->y && from->y+8 <= to->y+8){
		yover = 1;
	}
	
	if(xover && yover){
		return 1;
	} else {
		return 0;
	}
}

int overlaps_bulk(int froml, dyna* from, int tol, dyna* to){
	return 0;
}

void move_clump(clump* cl, int xdis, int ydis){
	
}

void set_clump_pos(clump* cl, int x, int y){
	
}

void set_clump_pal(clump* cl, int* pal){
	
}

void animate(mov_clump* anim){
	
}

#include "body.h"

void move_body(body* b, int xdis, int ydis){
	b->x += xdis;
	b->y += ydis;
	
	move_bulk(b->sprites, b->sprite_count, xdis, ydis);
}

void auto_body(body* b){
	b->yspd += b->g;
	move_body(b, b->xspd, b->yspd);
}

void xspd_in(body* b, int speed, int l, int r){
	b->xspd = (r-l)*speed;
}

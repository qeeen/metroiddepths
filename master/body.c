#include "body.h"

void move_body(body* b, int xdis, int ydis){
	b->x += xdis;
	b->y += ydis;
	
	move_bulk(b->sprites, b->sprite_count, xdis, ydis);
}

void auto_body(body* b){
	b->yspd += b->g;
	if (b->yspd > b->termv){
		b->yspd = b->termv;
	}
	if(b->yspd > 0){
		for(int i = 0; i < b->yspd; i++){
			if(is_solid(b->x, b->y+b->height)){
				b->yspd = 0;
				break;
			}
			move_body(b, 0, 1);
		}
	} else if(b->yspd < 0){
		for(int i = b->yspd; i <= 0; i++){
			if(is_solid(b->x, b->y-1)){
				b->yspd = 0;
				break;
			}
			move_body(b, 0, -1);
		}
	}
	move_body(b, b->xspd, 0);
}

void xspd_in(body* b, int speed, int l, int r){
	b->xspd = (r-l)*speed;
}

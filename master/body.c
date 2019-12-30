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

	if(b->xspd > 0){
		for(int i = 0; i < b->xspd; i++){
			for(int k =0; k < b->height; k++){
				if(is_solid(b->x+b->width, b->y+k)){
					b->xspd = 0;
					goto nested_break_x;
				}
			}
			move_body(b, 1, 0);
		}
	} else if(b->xspd < 0){
		for(int i = b->xspd; i <=0; i++){
			for(int k =0; k < b->height; k++){
				if(is_solid(b->x-1, b->y+k)){
					b->xspd = 0;
					goto nested_break_x;
				}
			}
			move_body(b, -1, 0);
		}
	}
	nested_break_x:
	
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

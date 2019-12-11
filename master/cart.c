#include "cart.h"
#include "stdnes.h"
#include "tiles.h"
#include <stdio.h>
#include <stdlib.h>

int* cartmain(int* inputs){
	int *spritebox;//816

	test_init();
	spritebox = grab_sprites();

	return spritebox;
}

#ifndef STDNES_H
#define STDNES_H

/// HEADERS ///
#include "globals.h"

#include <stdlib.h>

/// MACROS ///
#define byte unsigned char

/// FUNCTIONS ///
int getbit(byte dat, int bit);
int* get_bits(int n, int bitswanted);

#endif

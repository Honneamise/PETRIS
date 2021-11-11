#ifndef BLOCK_H
#define BLOCK_H

#include "../PIXIE/pixie_ext.h"

//a block is : { rows, cols, values... }
#define B0 (float []) { 4, 4, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0 }
#define B1 (float []) { 3, 3, 0, 1, 0, 0, 1, 0, 1, 1, 0 }
#define B2 (float []) { 3, 3, 0, 1, 0, 0, 1, 0, 0, 1, 1 }
#define B3 (float []) { 2, 2, 1, 1, 1, 1 }
#define B4 (float []) { 3, 3, 0, 1, 1, 1, 1, 0, 0, 0, 0 }
#define B5 (float []) { 3, 3, 0, 1, 0, 1, 1, 1, 0, 0, 0 }
#define B6 (float []) { 3, 3, 1, 1, 0, 0, 1, 1, 0, 0, 0 }

typedef struct Block
{
    int posx;
    int posy;

    PMatf mat;

} Block;

//functions
Block BlockInit(float *data);

Block BlockInitRandom();

void BlockClose(Block *b);

void BlockRotateR(Block *b);

void BlockRotateL(Block *b);

void BlockDraw(Block b, int32_t x, int32_t y, int32_t bg_color,int32_t fg_color, int32_t cell_size);

#endif
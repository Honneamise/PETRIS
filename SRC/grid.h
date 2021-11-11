#ifndef GRID_H
#define GRID_H

#include "../PIXIE/pixie_ext.h"
#include "block.h"

typedef struct Grid
{
    int x;
    int y;
    PMatf mat;

    int32_t cell_size;
    int32_t cell_bg;
    int32_t cell_fg;

} Grid;

Grid GridInit(int x, int y, int rows, int cols, int32_t cell_size, int32_t cell_bg, int32_t cell_fg);

void GridClose(Grid *g);

void GridDraw(Grid g);

int32_t GridBlockFit(Grid g, Block b);

int32_t GridRowFull(Grid g, int row);

void GridCopyBlock(Grid *g, Block b);

void GridShiftLow(Grid *g, int row_start);

int GridShift(Grid *g);

#endif

#include "../PIXIE/pixie_core.h"
#include "grid.h"

/**********/
Grid GridInit(int x, int y, int rows, int cols, int32_t cell_size, int32_t cell_bg, int32_t cell_fg)
{
    Grid g = {0};

    g.x = x;
    g.y = y;

    g.cell_size = cell_size;
    g.cell_bg = cell_bg;
    g.cell_fg = cell_fg;

    g.mat = PMatfInit(rows,cols,NULL);

    return g;
}

/**********/
void GridClose(Grid *g)
{
    PMatfClose(&g->mat);
}

/**********/
void GridDraw(Grid g)
{
    PixieColorSet(P_COLOR_0);        
    PixieDrawRectFill(g.x, g.y, g.mat.cols *g.cell_size, g.mat.rows*g.cell_size); 

    for(int i=0;i<g.mat.rows;i++)
    {
        for(int j=0;j<g.mat.cols;j++)
        {
            if(g.mat.data[i*g.mat.cols+j]==1)
            {
                PixieColorSet(g.cell_bg);        
                PixieDrawRectFill(g.x+j*g.cell_size, g.y+i*g.cell_size,g.cell_size, g.cell_size); 

                PixieColorSet(g.cell_fg);        
                PixieDrawRect(g.x+j*g.cell_size, g.y+i*g.cell_size,g.cell_size, g.cell_size); 

            }     
            // else
            // {
            //     PixieColorSet(P_COLOR_0);        
            //     PixieDrawRectFill(g.x+j*g.cell_size, g.y+i*g.cell_size,g.cell_size, g.cell_size); 

            // }
                
           
        }
    }
}

/**********/
int32_t GridBlockFit(Grid g, Block b)
{
    for(int i=0;i<b.mat.rows;i++)
    {
        for(int j=0;j<b.mat.rows;j++)
        {
            //if(b->mat->data[i][j]==1)
            if(PMatfGet(b.mat,i,j) == 1)
            {
                //WARNING THIS BLOCK CAN BE WRONG
                if(j+b.posx <  0)           { return 0; }
                if(j+b.posx >= g.mat.cols)  { return 0; }
                if(i+b.posy <  0)           { return 0; }
                if(i+b.posy >= g.mat.rows)  { return 0; }

                //if(g->mat->data[i+b->posy][j+b->posx]==1){ return 0;}
                if(PMatfGet(g.mat,i+b.posy, j+b.posx) == 1) { return 0; }
            }
        }
    }

    return 1;
}

/**********/
int32_t GridRowFull(Grid g, int row)
{
    for(int j=0;j<g.mat.cols;j++)
    {
        //if(g->mat->data[row][j]!=1) { return 0; }
        if(PMatfGet(g.mat,row,j)!=1) { return 0; }
    }

    return 1;
}

/**********/
void GridCopyBlock(Grid *g, Block b)
{
    for(int i=0;i<b.mat.rows;i++)
    {
        for(int j=0;j<b.mat.rows;j++)
        {
            //if(b->mat->data[i][j]==1)
            if(PMatfGet(b.mat,i,j) == 1)
            {
                //g->mat->data[i+b->posy][j+b->posx]=1;
                PMatfSet(g->mat,i+b.posy,j+b.posx,1);

            }
        }
    }
}

/**********/
void GridShiftLow(Grid *g, int row_start)
{
    for(int i=row_start;i>0;i--)
    {
        for(int j=0;j<g->mat.cols;j++)
        {
            //g->mat->data[i][j] = g->mat->data[i-1][j];

            float f = PMatfGet(g->mat,i-1,j);

            PMatfSet(g->mat,i,j,f);
        }
    }

    for(int j=0;j<g->mat.cols;j++)
    {
        //g->mat->data[0][j] = 0;

        PMatfSet(g->mat,0,j,0);
    }
}

/**********/
int GridShift(Grid *g)
{
    int lines = 0;

    for(int i=g->mat.rows-1;i>=0;i--)
    {
        if(GridRowFull(*g,i)){ GridShiftLow(g, i); i++; lines++;}
    }

    return lines;
}
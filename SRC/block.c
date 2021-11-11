#include "../PIXIE/pixie_core.h"
#include "../PIXIE/pixie_base.h"
#include "../PIXIE/pixie_ext.h"
#include "block.h"

/**********/
Block BlockInit(float *data)
{
    Block b = {0};

    b.mat = PMatfInit((int)data[0], (int)data[1], (float *)&data[2]);//maybe cast to float

    return b;
}

/**********/
Block BlockInitRandom()
{
    Block b = {0};

    int type = PRand(0,6);

    float *data = NULL;

    switch (type)
    {
        case 0:
            data = B0;
            break;

        case 1:
            data = B1;
            break;

        case 2:
            data = B2;
            break;

        case 3:
            data = B3;
            break;

        case 4:
            data = B4;
            break;

        case 5:
            data = B5;
            break;

        case 6:
            data = B6;
            break;
    
        default: break;
    }
    
    if(data!=NULL)
    {
        b.mat = PMatfInit((int)data[0], (int)data[1], (float*)&data[2]);//need cast to float ???
    }
    
    return b;
}

/**********/
void BlockClose(Block *b)
{
    PMatfClose(&b->mat);
}

/**********/
void BlockRotateR(Block *b)
{
    PMatfTranspose(b->mat,&b->mat);

    PMatfFlipH(b->mat,&b->mat);

}

/**********/
void BlockRotateL(Block *b)
{
    PMatfFlipH(b->mat,&b->mat);

    PMatfTranspose(b->mat,&b->mat);
}

/**********/
void BlockDraw(Block b, int32_t x, int32_t y, int32_t bg_color,int32_t fg_color, int32_t cell_size)
{
    int32_t _x = x+b.posx*cell_size; 
    int32_t _y = y+b.posy*cell_size;

    for(int i=0;i<b.mat.rows;i++)
    {
        for(int j=0;j<b.mat.cols;j++)
        {
            if(b.mat.data[i*b.mat.cols+j]==1)
            {
                PixieColorSet(bg_color); 
                PixieDrawRectFill(_x+j*cell_size, _y+i*cell_size, cell_size, cell_size); 

                PixieColorSet(fg_color); 
                PixieDrawRect(_x+j*cell_size, _y+i*cell_size, cell_size, cell_size);     
            }     
             
        }
    }
}
#define _CRT_SECURE_NO_WARNINGS
#include "stdio.h"

//pixie
#include "../PIXIE/pixie_core.h"

//stuff
#include "state.h"
#include "globals.h"

/**********/
void GameInit()
{
    

}

/*********/
void GameClose()
{
    
}

/*********/
void GameUpdate()
{
    if(GLOBALS.game_over){ return; }

    if(PixieTimeGet()- GLOBALS.time_check > GLOBALS.delay)
    {
        GLOBALS.cur_block.posy +=1;
        if(GridBlockFit(GLOBALS.grid, GLOBALS.cur_block)){ GLOBALS.time_check = PixieTimeGet(); }
        else
        {
            GLOBALS.cur_block.posy -=1;

            GridCopyBlock(&GLOBALS.grid,GLOBALS.cur_block);

            BlockClose(&GLOBALS.cur_block);

            GLOBALS.cur_block = GLOBALS.next_block;
            if(!GridBlockFit(GLOBALS.grid, GLOBALS.cur_block)){ GLOBALS.game_over = 1; }

            GLOBALS.next_block = BlockInitRandom();
            GLOBALS.next_block.posx = GLOBALS.grid.mat.cols/2-GLOBALS.next_block.mat.cols/2;
    
            int32_t val = GridShift(&GLOBALS.grid);

            GLOBALS.lines += val;

            if(val!=0){ GLOBALS.delay -= 50; }
        }
    }
}

/**********/
void GameInput()
{
    while(PixieEventAvailable())
    {
        if(PixieEventGetType() == P_QUIT) { SM_Stop(); }

        if(GLOBALS.game_over)
        {
            if(PixieEventGetType()==P_KEYPRESS && PixieEventGetKey()== P_ENTER) 
            { 
                SM_Push(MENU_STATE);
            }
            else
            {
                continue;
            }
        }

        if(PixieEventGetType() == P_KEYPRESS && PixieEventGetKey() == P_ESC )
        {
            SM_Push(OPTIONS_STATE);
        }

        if(PixieEventGetType() == P_KEYPRESS )
        { 
            int32_t key = PixieEventGetKey();

            switch(key)
            {
                case P_UP:
                    BlockRotateR(&GLOBALS.cur_block);
                    if(!GridBlockFit(GLOBALS.grid,GLOBALS.cur_block)){BlockRotateL(&GLOBALS.cur_block);}
                    break;

                case P_DOWN:
                    GLOBALS.cur_block.posy +=1;
                    if(!GridBlockFit(GLOBALS.grid,GLOBALS.cur_block)){GLOBALS.cur_block.posy -=1;}
                    break;

                case P_LEFT:
                    GLOBALS.cur_block.posx -=1;
                    if(!GridBlockFit(GLOBALS.grid,GLOBALS.cur_block)){GLOBALS.cur_block.posx +=1;}
                    break;

                case P_RIGHT:
                    GLOBALS.cur_block.posx +=1;
                    if(!GridBlockFit(GLOBALS.grid,GLOBALS.cur_block)){GLOBALS.cur_block.posx -=1;}
                    break;

                default: break;

            }
            
        }

    }

}
	
/**********/
void GameDraw()
{
    PixieRenderClear(P_COLOR_0);

    PixieDrawImage(GLOBALS.bg,GLOBALS.bg_w,GLOBALS.bg_h,0,0);

    GridDraw(GLOBALS.grid);

    BlockDraw(GLOBALS.cur_block,GLOBALS.grid.x,GLOBALS.grid.y,GLOBALS.grid.cell_bg,GLOBALS.grid.cell_fg,GLOBALS.grid.cell_size);
    
    //sfondo a dx
    int32_t _x = WINDOW_W/4*3-GRID_COLS*CELL_SIZE/2;
    PixieColorSet(P_COLOR_0);        
    PixieDrawRectFill(_x, 50, GRID_COLS*CELL_SIZE, GRID_ROWS/5*3*CELL_SIZE); 

    BlockDraw(GLOBALS.next_block,_x-CELL_SIZE,150,GLOBALS.grid.cell_bg,GLOBALS.grid.cell_fg,GLOBALS.grid.cell_size);

    PixieFontSetScale(3);
    PixieColorSet(P_COLOR_3);

    PixieDrawString("   Next",_x,100);
    
    char score_str[24] = {0};
    sprintf(score_str,"   Score\n\n   %d",GLOBALS.lines*10);
    PixieDrawString(score_str,_x,250);

    if(GLOBALS.game_over)
    {
        PixieColorSet(P_COLOR_0);

        PixieDrawRectFill(0,WINDOW_H/4,WINDOW_W,WINDOW_H/2);

        int32_t w = 0;
        int32_t h = 0;
        
        PixieColorSet(P_COLOR_3);

        //
        PixieFontSetScale(6);

        PixieFontGetStringSize(GAME_OVER_STR,&w,&h);  

        PixieDrawString(GAME_OVER_STR,WINDOW_W/2-w/2,WINDOW_H/4+h/2);

        //
        char score_final_str[24] = {0};
        sprintf(score_final_str,"Score : %d",GLOBALS.lines*10);

        PixieFontGetStringSize(score_final_str,&w,&h);  

        PixieDrawString(score_final_str,WINDOW_W/2-w/2,WINDOW_H/2);

        //
        PixieFontSetScale(3);

        PixieFontGetStringSize(PRESS_KEY_STR,&w,&h);

        PixieDrawString(PRESS_KEY_STR,WINDOW_W/2-w/2,WINDOW_H/4*3-h*2);
    }

    PixieRenderDraw();

}
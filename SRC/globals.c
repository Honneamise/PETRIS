
//includes
#include "globals.h"



//vars
Globals GLOBALS = {0};

/**********/
void GlobalsInit()
{
    //generic
    PixieImageLoad("RES/bg.bmp",&GLOBALS.bg,&GLOBALS.bg_w,&GLOBALS.bg_h);

    PixieAudioLoadSound("RES/music.wav",&GLOBALS.music,&GLOBALS.music_size,&GLOBALS.music_format,&GLOBALS.music_rate);

    PixieAudioLoopSound(GLOBALS.music,GLOBALS.music_size,GLOBALS.music_format,GLOBALS.music_rate);
  
    GlobalsResetGame();

}

/**********/
void GlobalsClose()
{
    PFree(GLOBALS.bg);

    PixieAudioStopSound();

    PFree(GLOBALS.music);

    GridClose(&GLOBALS.grid);

    BlockClose(&GLOBALS.cur_block);

    BlockClose(&GLOBALS.next_block);

}

/**********/
void GlobalsResetGame()
 {
    GridClose(&GLOBALS.grid);

    BlockClose(&GLOBALS.cur_block);

    BlockClose(&GLOBALS.next_block);

    GLOBALS.grid = GridInit(GRID_X, GRID_Y,GRID_ROWS,GRID_COLS,CELL_SIZE,CELL_BG,CELL_FG);

    GLOBALS.cur_block = BlockInitRandom();
    GLOBALS.cur_block.posx = GLOBALS.grid.mat.cols/2-GLOBALS.cur_block.mat.cols/2;

    GLOBALS.next_block = BlockInitRandom();
    GLOBALS.next_block.posx = GLOBALS.grid.mat.cols/2-GLOBALS.next_block.mat.cols/2;
    
    GLOBALS.delay = 1000;

    GLOBALS.time_check = PixieTimeGet();

    GLOBALS.game_over = 0;
 } 
  
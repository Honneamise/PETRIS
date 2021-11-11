#ifndef GLOBALS_H
#define GLOBALS_H

/***********/
/* INCLUDE */
/***********/
#include "../PIXIE/pixie_core.h"
#include "../PIXIE/pixie_base.h"

#include "block.h"
#include "grid.h"

/***********/
/* DEFINES */
/***********/
//defines
#define WINDOW_W        800
#define WINDOW_H        600

#define GRID_X          WINDOW_W/4-GRID_COLS*CELL_SIZE/2
#define GRID_Y          WINDOW_H/2-GRID_ROWS*CELL_SIZE/2
#define GRID_ROWS       20
#define GRID_COLS       10

#define CELL_SIZE       25
#define CELL_BG         P_COLOR_1
#define CELL_FG         P_COLOR_2

#define MENU_STATE      "MENU"
#define GAME_STATE      "GAME"
#define OPTIONS_STATE   "OPTIONS"

#define GAME_OVER_STR   "GAME OVER\n"
#define PRESS_KEY_STR   "Press Enter to continue"
#define PETRIS_STR      "PETRIS"
/************/
/* TYPEDEFS */
/************/
typedef struct Globals
{
    PImage bg;
    int32_t bg_w;
    int32_t bg_h;

    PSound music;
    int32_t music_size;
    int32_t music_format;
    int32_t music_rate;
    
    Block cur_block;
    Block next_block;
    Grid grid;

    int32_t game_over;
    int32_t lines;

    int32_t delay;
    int32_t time_check;

}Globals;

/********/
/* VARS */
/********/
Globals GLOBALS; 

/*********/
/* FUNCS */
/*********/
void GlobalsInit();

void GlobalsClose();

void GlobalsResetGame();

#endif
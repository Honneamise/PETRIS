
//pixie
#include "../PIXIE/pixie_core.h"

//stuff
#include "globals.h"

#include "state.h"
#include "menu.h"
#include "game.h"
#include "options.h"

int main (int argc, char **argv)
{ 
    PixieDebug();

    PixieInit(WINDOW_W,WINDOW_H,0);

    PixiePaletteSet(1);
    
    PixieToggleVsync();
    
    GlobalsInit();

    State menu = StateInit(MENU_STATE, MenuInit, MenuClose, MenuUpdate, MenuInput, MenuDraw);
    State game = StateInit(GAME_STATE, GameInit, GameClose, GameUpdate, GameInput, GameDraw);
    State options = StateInit(OPTIONS_STATE, OptionsInit, OptionsClose, OptionsUpdate, OptionsInput, OptionsDraw);

    SM_Init();
    
    SM_Add(&menu);
    SM_Add(&game);
    SM_Add(&options);
    
    SM_Push(MENU_STATE);
    
    SM_Start();

    SM_Close();

    GlobalsClose();

    PixieClose();
}
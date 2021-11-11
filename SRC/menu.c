//pixie
#include "../PIXIE/pixie_core.h"
#include "../PIXIE/pixie_gui.h"

//stuff
#include "globals.h"
#include "state.h"

//vars
static PixieGui gui = {0};

static int32_t b_play = 0;
static int32_t b_options = 0;
static int32_t b_quit = 0;

/**********/
void MenuInit()
{
    gui = PixieGuiInit(NULL,4,P_COLOR_0,P_COLOR_1);

    b_play = PixieGuiAddButton(&gui,50,300,"PLAY");
    b_options = PixieGuiAddButton(&gui,50,400,"OPTIONS");
    b_quit = PixieGuiAddButton(&gui,50,500,"QUIT");
    
}

/*********/
void MenuClose()
{
    PixieGuiClose(&gui);
}

/*********/
void MenuUpdate()
{
    if(PixieGuiGetActiveId(&gui)==b_play) { GlobalsResetGame(); SM_Push(GAME_STATE); }

    if(PixieGuiGetActiveId(&gui)==b_options) { SM_Push(OPTIONS_STATE); }

    if(PixieGuiGetActiveId(&gui)==b_quit) { SM_Stop(); }

}

/**********/
void MenuInput()
{
    PixieGuiClearEvents(&gui);

    while(PixieEventAvailable())
    {
        if(PixieEventGetType() == P_QUIT) { SM_Stop(); }

        PixieGuiHandleEvent(&gui);
    }
}
	
/**********/
void MenuDraw()
{
    PixieRenderClear(P_COLOR_0);

    PixieDrawImage(GLOBALS.bg,GLOBALS.bg_w,GLOBALS.bg_h,0,0);

    PixieGuiDraw(gui);

    PixieFontSetScale(15);

    int32_t w = 0;
    int32_t h = 0;

    PixieFontGetStringSize(PETRIS_STR,&w,&h);

    PixieColorSet(P_COLOR_0);

    PixieDrawString(PETRIS_STR, WINDOW_W/2-w/2,50);

    PixieRenderDraw();
}
#define _CRT_SECURE_NO_WARNINGS
#include "stdio.h" //remove me

//pixie
#include "../PIXIE/pixie_core.h"
#include "../PIXIE/pixie_gui.h"

//stuff
#include "globals.h"
#include "state.h"

static PixieGui gui = {0};

static int32_t sound = 0;
static int32_t sound_val = 50;

static int32_t music = 0;
static int32_t music_val = 50;

static int32_t palette = 0;
static int32_t palette_val = 0;
static char **palette_options = (char*[]){"PALETTE 1",
                                        "PALETTE 2",
                                        "PALETTE 3",
                                        "PALETTE 4",
                                        "PALETTE 5",
                                        "PALETTE 6"  };

static int32_t screen = 0;
static int32_t screen_val = 0;

static int32_t back = 0;

/**********/
void OptionsInit()
{
    gui = PixieGuiInit(NULL,4,P_COLOR_0,P_COLOR_1);

    sound = PixieGuiAddSlider(&gui,50,100,10,&sound_val,0,100);

    music = PixieGuiAddRadio(&gui,50,200,&music_val);

    screen = PixieGuiAddRadio(&gui,50,300,&screen_val);

    palette = PixieGuiAddSelector(&gui,50,400,&palette_val,6,palette_options);

    back = PixieGuiAddButton(&gui,650,50,"BACK");

}

/*********/
void OptionsClose()
{
    PixieGuiClose(&gui);
}

/*********/
void OptionsUpdate()
{
    if(PixieGuiGetActiveId(&gui) == sound)
    {
        PixieAudioSetVolume(sound_val/100.0f);
    }

    if(PixieGuiGetActiveId(&gui) == music)
    {
        if(music_val==0){ PixieAudioStopSound(); }
        else{ PixieAudioLoopSound(GLOBALS.music,GLOBALS.music_size,GLOBALS.music_format,GLOBALS.music_rate); }
    }

    if(PixieGuiGetActiveId(&gui) == screen)
    {
        PixieToggleFullScreen();
    }

    if(PixieGuiGetActiveId(&gui) == palette)
    {
        PixiePaletteSet(1+palette_val);
    }

    if(PixieGuiGetActiveId(&gui) == back)
    {
        SM_Pop();
    }

}

/**********/
void OptionsInput()
{
    PixieGuiClearEvents(&gui);

    while(PixieEventAvailable())
    {
        if(PixieEventGetType() == P_QUIT) { SM_Stop(); }

        PixieGuiHandleEvent(&gui);
    }
}
	
/**********/
void OptionsDraw()
{
    PixieRenderClear(P_COLOR_0);

    PixieDrawImage(GLOBALS.bg,GLOBALS.bg_w,GLOBALS.bg_h,0,0);

    PixieColorSet(P_COLOR_0);
    PixieFontSetScale(4);

    char vol_str[24] = {0};
    sprintf(vol_str,"Volume %d", sound_val);
    PixieDrawString(vol_str, 50, 50);

    PixieDrawString("Music", 50, 150);

    PixieDrawString("Fullscreen", 50, 250);

    PixieDrawString("Palette", 50, 350);

    PixieGuiDraw(gui);

    //controls
    char controls[] = "CONTROLS\n\nUP   :ROTATE\nDOWN :MOVE DOWN\nLEFT :MOVE LEFT\nRIGHT:MOVE RIGHT\nESC  :OPTIONS";
    
    PixieFontSetScale(3);
    int32_t w = 0;
    int32_t h = 0;
    PixieFontGetStringSize(controls,&w,&h);


    PixieColorSet(P_COLOR_0);
    PixieDrawRectFill(WINDOW_W-w-25,400,w,h);

    PixieColorSet(P_COLOR_1);
    PixieDrawString(controls,WINDOW_W-w-25, 400);

    PixieRenderDraw();
}
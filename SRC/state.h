#ifndef STATE_H
#define STATE_H

#include "stdint.h"
#include "../PIXIE/pixie_core.h"
#include "../PIXIE/pixie_base.h"

/*********/
/* STATE */
/*********/
typedef struct State
{
	char* name;

	void(*init)();
    void(*close)();

    void(*update)();
	void(*input)();
	void(*draw)();

}State;

State StateInit(char *name, void(*init)(), void(*close)(), void(*update)(), void(*input)(), void(*draw)() );

void StateClose(State *state);


/*****************/
/* STATE MANAGER */
/*****************/
typedef struct StateManager
{
    int32_t run;
    State *push;
    State *pop;
    PArray states;
    PStack stack;

}StateManager;

void SM_Init();

void SM_Close();

void SM_Add(State *st);

void SM_Push(char *name);

void SM_Pop();

void SM_Start();

void SM_Stop();

#endif
#include "assert.h"
#include "string.h"

#include "state.h"

static StateManager SM = {0};

/*********/
/* STATE */
/*********/
State StateInit(char *name, void(*init)(), void(*close)(), void(*update)(), void(*input)(), void(*draw)() )
{
    return (State){ name, init, close, update, input, draw };
}

/*********/
void StateClose(State *state)
{
    state->close();

	state->name = NULL;
	state->init = NULL;
	state->close = NULL;
	state->update = NULL;
	state->input = NULL;
	state->draw = NULL;
}

/*****************/
/* STATE MANAGER */
/*****************/
void SM_Init()
{
	SM.run = 0;
    SM.push = NULL;
    SM.pop = NULL; 
    PArrayInit(&SM.states);
	PStackInit(&SM.stack);
}

/**********/
void SM_Close()
{
	SM.run = 0;
	SM.push = NULL;
    SM.pop = NULL; 

	PArrayClose(&SM.states, (void (*)(void *))StateClose );
	PStackClose(&SM.stack,NULL);
}

/**********/
void SM_Add(State *st)
{	
	for(int i=0;i<SM.states.elems_count;i++)
	{
		if(strcmp( ((State*)(SM.states.elems[i]))->name, st->name)==0)
		{
			//state already inserted, skip
			return;
		}
	}

	st->init();

	PArrayAdd(&SM.states,st);
}

/**********/
void SM_Push(char *name)
{
	assert(name!=NULL);

	for(int i=0;i<SM.states.elems_count;i++)
	{
		if(strcmp( ((State*)(SM.states.elems[i]))->name, name)==0)
		{
			SM.push = (State*)(SM.states.elems[i]);
			return;
		}
	}

	//if here state not found
}

/**********/
void SM_Pop()
{
	SM.pop = PStackPeek(&SM.stack);
}

/**********/
void SM_Start()
{
	SM.run = 1;

    while(SM.run)
	{
		if(SM.push)
		{
			PStackPush(&SM.stack,SM.push);
			SM.push = NULL;
			PixieEventClearQueue();
		}

		if(SM.pop)
		{
			PStackPop(&SM.stack);
			SM.pop = NULL;
			PixieEventClearQueue();
		}

    	State *state = PStackPeek(&SM.stack);

		if(state)
		{
			if(state->input) { state->input(); };

			if(state->update) { state->update(); };

			if(state->draw) { state->draw(); };
		}
		else
		{ 
			SM.run=0; 
		}
	
	}
}

/**********/
void SM_Stop()
{
	SM.run = 0;
}
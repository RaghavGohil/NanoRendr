#include "input.h"
#include "../types.h"
#include "../global.h"

//MOUSE:
static IVec2 mouse_pos = {0};
//MOUSE POSITION:
void set_mouse_pos(IVec2 *v)
{
	SDL_GetMouseState(&v->x,&v->y);
}

IVec2 get_mouse_pos()
{
	return mouse_pos;
}

//handles all the inputs
void handle_input(bool *exit)
{
	SDL_Event e;
	global.input.event = e;
	while(SDL_PollEvent(&e))
	{
		switch(e.type)
		{
			case SDL_QUIT:
				*exit = true; // directly quit out of the engine
				break;
			case SDL_MOUSEMOTION:
				set_mouse_pos(&mouse_pos);
				break;
			default:
				break;
		}	
	}
	
} 

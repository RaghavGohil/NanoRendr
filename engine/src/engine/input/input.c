#include "input.h"
#include "../types.h"
#include "../global.h"

//MOUSE:
inline void set_mouse_pos()
{
	SDL_GetMouseState(&global.input.mouse_pos.x,&global.input.mouse_pos.y);
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
				set_mouse_pos();
				break;
			default:
				break;
		}	
	}
	
} 

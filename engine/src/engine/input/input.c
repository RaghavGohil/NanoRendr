#include "input.h"
#include "../types.h"
#include "../global.h"

//MOUSE:
inline void set_mouse_pos(void)
{
	int x,y;
	SDL_GetMouseState(&x,&y);
	global.input_handler.mouse_pos[0] = x;
	global.input_handler.mouse_pos[1] = y; 
}

//handles all the inputs
void handle_input(bool *exit)
{
	SDL_Event e;
	global.input_handler.event = e;
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

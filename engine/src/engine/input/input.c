#include "input.h"

static IVec2 mouse_pos = {0};

void handle_input(SDL_Event *e,bool *exit)
{
	switch(e->type)
	{
		case SDL_QUIT:
			*exit = true;
			break;
		case SDL_MOUSEMOTION:
			set_mouse_pos(&mouse_pos);
			break;
		default:
			break;
	}
} 

void set_mouse_pos(IVec2 *v)
{
	SDL_GetGlobalMouseState(&v->x,&v->y);	
}

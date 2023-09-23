#pragma once

#include <SDL2/SDL.h>

#include "../types.h"
#include "../math/math.h"
#include <stdbool.h>

//KEYS:
typedef enum input_keys
{
	DEFAULT_KEY,	
}INPUT_KEYS;

void handle_input(SDL_Event *e,bool *exit); // handles all the events 

//events which will be checked in handle_input
void set_mouse_pos(IVec2 *); // sets the mouse pos

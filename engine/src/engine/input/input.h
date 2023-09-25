#pragma once

#include <SDL2/SDL.h>

#include "../types.h"
#include "linmath.h"
#include <stdbool.h>
#include "../math/math.h"

typedef struct input_state
{
	SDL_Event event;
	//KEYS:
	//MOUSE:
	IVec2 mouse_pos;
}Input_State;

//KEYS:
typedef enum input_keys
{
	DEFAULT_KEY,	
}Input_Keys;

//events which will be checked in handle_input
void handle_input(bool *exit); // handles all the events 

//MOUSE:
//MOUSE POSITION
void set_mouse_pos();//sets the mouse pos

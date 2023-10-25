#pragma once

#include <SDL2/SDL.h>

#include "../types.h"
#include "linmath.h"
#include <stdbool.h>

typedef struct input
{
	SDL_Event event;
	//MOUSE:
	vec2 mouse_pos;
}Input_State;

//events which will be checked in handle_input
void handle_input(bool *exit); // handles all the events 

//MOUSE:
//MOUSE POSITION
void set_mouse_pos(void);//sets the mouse pos

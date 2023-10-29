#pragma once

#include <SDL2/SDL.h>
#include <linmath.h>
#include "render_internal.h"

#include "../types.h"

typedef struct renderer
{
	mat4x4 projection,view;
}Renderer;

typedef struct window 
{
	SDL_Window *window;
	f32 width;
	f32 height;
	char *title;
	Renderer renderer;
}Window;

void render_init(u32 height, u32 width, char* title);
static SDL_Window* render_init_window(u32 height, u32 width, char* title);
void render_begin(void);
void render_end(void);
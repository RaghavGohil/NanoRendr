#pragma once

#include <SDL2/SDL.h>

#include "../types.h"
#include "render.h"

typedef struct render_state_internal 
{
	u32 vao_quad;
	u32 vbo_quad;
	u32 ebo_quad;
} Render_State_Internal;

SDL_Window *render_init_window(u32 height, u32 width);
void render_init_quad(u32 *vao, u32 *vbo, u32 *ebo);

#pragma once

#include "render/render.h"
#include "input/input.h"

typedef struct global
{
	Render_State render;
	Input_State input;
}Global;

extern Global global;

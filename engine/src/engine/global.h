#pragma once

#include "render/render.h"
#include "input/input.h"
#include "camera/camera.h"

typedef struct global
{
	Window window;
	Input_Handler input_handler;
}Global;

extern Global global;

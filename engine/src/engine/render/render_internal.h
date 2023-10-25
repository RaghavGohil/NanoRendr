#pragma once

#include <SDL2/SDL.h>

#include <linmath.h>
#include "../types.h"
#include "render.h"

typedef struct sprite 
{
	u32 vao;
	u32 vbo;
	u32 ebo;
	u32 shader;
	u32 texture;
	mat4x4 model;
	vec4 color;
}Sprite;

Sprite* create_sprite(const char* path_image);
void blit_sprite(Sprite* sprite, vec2 pos, vec2 size, vec4 color);
void create_texture(u32 *texture);
void set_shaders(Sprite* sprite);
u32 create_shader(const char *path_vert, const char *path_frag);
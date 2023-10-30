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
	i32 width,height;
}Sprite;

typedef struct sprite_sheet
{
	Sprite sprite; // sprite is the entire sheet here (as of now)
	u32 rows,columns;
}Sprite_Sheet;

Sprite* create_sprite(const char* path_image);
void blit_sprite(Sprite* sprite, vec2 pos, vec2 size , vec4 color);
static void create_texture(const char* path, u32 *texture,i32* width, i32* height);
static void set_shaders(u32 *shader);
static u32 create_shader(const char *path_vert, const char *path_frag);
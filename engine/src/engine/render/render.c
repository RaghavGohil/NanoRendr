#include <glad/glad.h>
#include "../global.h"
#include "render.h"
#include "render_init.h"
#include <stdio.h>

static Render_State_Internal state = {0};

void render_init(u32 width, u32 height, char *title)
{
	global.render.width = width;
	global.render.height = height;
	global.render.title = title;
	global.render.window = render_init_window(global.render.width,global.render.height,global.render.title);
	render_init_quad(&state.vao_quad, &state.vbo_quad, &state.ebo_quad);
	render_init_shaders(&state);
	render_init_color_texture(&state.texture_color);
}

void render_begin(void)
{
	glClearColor(0.08,0.1,0.1,1); // specifies which color to put when screen is cleared
	glClear(GL_COLOR_BUFFER_BIT); // we are using the color buffer
}

void render_end(void)
{
	SDL_GL_SwapWindow(global.render.window); // update the screen
}

void render_quad(vec2 pos, vec2 size, vec4 color)
{
	glUseProgram(state.shader_default);
	mat4x4 model;
	mat4x4_identity(model);
	mat4x4_translate(model,pos[0],pos[1],0);
	mat4x4_scale_aniso(model,model,size[0],size[1],1);
	glUniformMatrix4fv(glGetUniformLocation(state.shader_default,"model"),1,GL_FALSE,&model[0][0]);
	glUniform4fv(glad_glGetUniformLocation(state.shader_default,"color"),1,color);
	glBindVertexArray(state.vao_quad);
	glBindTexture(GL_TEXTURE_2D,state.texture_color);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, NULL);
	glBindVertexArray(0);
}

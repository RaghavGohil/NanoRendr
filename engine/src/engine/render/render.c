#include <glad/glad.h>
#include "../global.h"
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#include "render.h"
#include "render_internal.h"
#include <stdio.h>

static Window window= {0};

SDL_Window *render_init_window(u32 width, u32 height, char* title)
{
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK,SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION,3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION,3);

	if(SDL_Init(SDL_INIT_VIDEO) != 0)
		ERROR_EXIT("Failed to initalize SDL%s\n",SDL_GetError());

	SDL_Window *window = SDL_CreateWindow
	(
		title,	
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		width,
		height,
		SDL_WINDOW_OPENGL 
	);
	
	if(!window) 
		ERROR_EXIT("Failed to initialize the window! %s\n",SDL_GetError());		
	SDL_GL_CreateContext(window);

	if(!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress)) //load the gl function pointers
		ERROR_EXIT("Failed to load GL! %s\n",SDL_GetError());

	printf("OpenGL loaded.\n");
	printf("Vendor:   %s\n",glGetString(GL_VENDOR));
	printf("Renderer: %s\n",glGetString(GL_RENDERER));
	printf("Version:  %s\n",glGetString(GL_VERSION));

	return window;
}

/*void render_init(u32 width, u32 height, char *title)
{
	global.window.width = width;
	global.window.height = height;
	global.window.title = title;
	global.window.window = render_init_window(global.window.width,global.window.height,global.window.title);
	render_init_quad(&state.vao_quad, &state.vbo_quad, &state.ebo_quad);
	render_init_shaders(&state);
	render_init_color_texture(&state.texture_color);
}*/

void render_begin(void)
{
	glClearColor(0.08,0.1,0.1,1); // specifies which color to put when screen is cleared
	glClear(GL_COLOR_BUFFER_BIT); // we are using the color buffer
}

void render_end(void)
{
	SDL_GL_SwapWindow(global.window.window); // update the screen
}

void render_quad(vec2 pos, vec2 size, vec4 color)
{
	glUseProgram();
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

#include <glad/glad.h>
#include <SDL2/SDL.h>

#include "../util.h"
#include "../types.h"
#include "../global.h"
#include "../io/io.h"

#include "render.h"
#include "render_init.h"

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

void render_init_quad(u32 *vao, u32 *vbo, u32 *ebo)
{
	//x,y,z,u,v
	f32 vertices[] = 
	{
		0.5,0.5,0,0,0,
		0.5,-0.5,0,0,1,
		-0.5,-0.5,0,1,1,
		-0.5,0.5,0,1,0
	};

	//separate triangular connections
	u32 indices[] = 
	{
		0,1,3,
		1,2,3
	};

	glGenVertexArrays(1,vao);
	glGenBuffers(1,vbo);
	glGenBuffers(1,ebo);

	glBindVertexArray(*vao);

	glBindBuffer(GL_ARRAY_BUFFER,*vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,*ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,5*sizeof(f32),NULL);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1,2,GL_FLOAT,GL_FALSE,5*sizeof(f32),(void*)(3*sizeof(f32)));
	glad_glEnableVertexAttribArray(1);
}
void render_init_color_texture(u32 *texture)
{
	glGenTextures(1,texture);
	glBindTexture(GL_TEXTURE_2D, *texture);
	u8 solid_white[4] = {255,255,255,255};		
	glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA,1,1,0,GL_RGBA,GL_UNSIGNED_BYTE,solid_white);
	glBindTexture(GL_TEXTURE_2D,0);
}
void render_init_shaders(Render_State_Internal *state)
{
	state->shader_default = render_shader_create("./shaders/default.vert","./shaders/default.frag");
	mat4x4_ortho(state->projection,0,global.render.width,global.render.height,0,-2,2); // to simulate the sdl game engines.
	glUseProgram(state->shader_default);
	glUniformMatrix4fv
	(
		glGetUniformLocation(state->shader_default,"projection"),
		1,
		GL_FALSE,
		&state->projection[0][0]
	);
}
u32 render_shader_create(const char *path_vert, const char *path_frag)
{
	int success=0;
	char log[512];
	File file_vertex = read_file(path_vert);
	if(!file_vertex.isValid)
	{
		ERROR_EXIT("Error loading shader %s\n",path_vert);
	}

	u32 shader_vertex = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(shader_vertex,1,(const char * const *)&file_vertex,NULL);
	glCompileShader(shader_vertex);
	glGetShaderiv(shader_vertex,GL_COMPILE_STATUS,&success);
	if(!success)
	{
		glGetShaderInfoLog(shader_vertex,512,NULL,log);
		ERROR_EXIT("Error compiling vertex shader. %s\n",log);
	}

	File file_fragment = read_file(path_frag);

	if(!file_fragment.isValid)
	{
		ERROR_EXIT("Error loading shader %s\n",path_frag);
	}

	u32 shader_fragment= glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(shader_fragment,1,(const char *const *)&file_fragment,NULL);
	glCompileShader(shader_fragment);
	glGetShaderiv(shader_fragment,GL_COMPILE_STATUS,&success);
	if(!success)
	{
		glGetShaderInfoLog(shader_fragment,512,NULL,log);
		ERROR_EXIT("Error compiling fragment shader. %s\n",log);
	}

	u32 shader = glCreateProgram();
	glAttachShader(shader,shader_vertex);
	glAttachShader(shader,shader_fragment);
	glLinkProgram(shader);
	glGetProgramiv(shader,GL_LINK_STATUS,&success);
	if(!success)
	{
		glGetProgramInfoLog(shader,512,NULL,log);
		ERROR_EXIT("Error linking shader. %s\n",log);
	}
	free(file_vertex.data);
	free(file_fragment.data);
	return shader;
}

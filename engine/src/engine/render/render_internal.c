#include <glad/glad.h>
#include <SDL2/SDL.h>

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

#include "../util.h"
#include "../types.h"
#include "../global.h"
#include "../io/io.h"

#include "render.h"
#include "render_internal.h"

Sprite* create_sprite(const char* path)
{
	Sprite *res = (Sprite*) malloc(sizeof(Sprite));

	f32 vertices[] = 
	{
		1,1,0,    0,0,
		1,-1,0,   0,1,
		-1,-1,0,  1,1,
		-1,1,0,   1,0
	};

	u32 indices[] = 
	{
		0,1,3,
		1,2,3
	};

	glGenVertexArrays(1,&res->vao);
	glGenBuffers(1,&res->vbo);
	glGenBuffers(1,&res->ebo);

	glBindVertexArray(res->vao);

	glBindBuffer(GL_ARRAY_BUFFER,res->vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,res->ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,5*sizeof(f32),NULL);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1,2,GL_FLOAT,GL_FALSE,5*sizeof(f32),(void*)(3*sizeof(f32)));
	glEnableVertexAttribArray(1);
	create_texture(path,&res->texture,&res->width,&res->height);


	set_shaders(&res->shader);

	return res;
}

void blit_sprite(Sprite* sprite, vec2 pos, vec2 size, vec4 color)
{
	glUseProgram(sprite->shader);
	mat4x4_identity(sprite->model);
	mat4x4_translate(sprite->model,pos[0],pos[1],0);
	mat4x4_scale_aniso(sprite->model,sprite->model,-size[0],size[1],1); // to avoid the horizontal flipping 
	glUniformMatrix4fv(glGetUniformLocation(sprite->shader,"model"),1,GL_FALSE,&sprite->model[0][0]);
	glUniform4fv(glad_glGetUniformLocation(sprite->shader,"color"),1,color);
	glBindVertexArray(sprite->vao);
	glBindTexture(GL_TEXTURE_2D,sprite->texture);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, NULL);
	glBindVertexArray(0);
}

static void create_texture(const char* path, u32 *texture, i32* width, i32* height)
{
	i32 nr_channels;
	glGenTextures(1,texture);
	glBindTexture(GL_TEXTURE_2D, *texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	// gl repeat is by default
	if(path == NULL)
	{
		u8 no_texture[4] = {255,0,255,255}; // for sprites with no textures		
		glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA,1,1,0,GL_RGBA,GL_UNSIGNED_BYTE,no_texture);
	}
	else
	{
		unsigned char *data = stbi_load(path,width,height,&nr_channels,0);
		if(data != NULL)
		{
			if(nr_channels == 3)
				glTexImage2D(GL_TEXTURE_2D,0,GL_RGB,*width,*height,0,GL_RGB,GL_UNSIGNED_BYTE,data);
			if(nr_channels == 4)
				glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA,*width,*height,0,GL_RGBA,GL_UNSIGNED_BYTE,data);
		}
		else
			ERROR_EXIT("Unable to load texture file. At %s.", path);
		stbi_image_free(data);
	}
	glGenerateMipmap(GL_TEXTURE_2D);
}
static void set_shaders(u32 *shader)
{
	*shader = create_shader("./shaders/default.vert","./shaders/default.frag");
	glUseProgram(*shader);
	glUniformMatrix4fv
	(
		glGetUniformLocation(*shader,"projection"),
		1,
		GL_FALSE,
		&global.window.renderer.projection[0][0]
	);
	glUniformMatrix4fv
	(
		glGetUniformLocation(*shader,"view"),
		1,
		GL_FALSE,
		&global.window.renderer.view[0][0]
	);
}
static u32 create_shader(const char *path_vert, const char *path_frag)
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

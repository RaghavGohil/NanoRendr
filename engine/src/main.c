#include<stdio.h>
#include<stdbool.h>
#define SDL_MAIN_HANDLED //define this!!!
#include "engine/global.h"

#pragma region CONFIG 

#define SCREEN_WIDTH 600 
#define SCREEN_HEIGHT 600 

static bool quit = false;

#pragma endregion

#pragma region GAME

vec2 ship_pos = {0,0};
vec2 rotate_dir = {0,0};
vec2 mouse_pos = {0,0};

#pragma endregion

void init()
{
	//ship:	
	ship_pos[0]= SCREEN_WIDTH;
	ship_pos[1] = SCREEN_HEIGHT;

	//engine:	
	render_init(SCREEN_WIDTH,SCREEN_HEIGHT,"NanoRendr Engine");	
}

void move_ship()
{
	//rotate to mouse:
	mouse_pos[0] = global.input_handler.mouse_pos[0];
	mouse_pos[1] = global.input_handler.mouse_pos[1];
	rotate_dir[0]= ship_pos[0]- mouse_pos[0];
	rotate_dir[1]= ship_pos[1]- mouse_pos[1];
}

int main(int argc,char* argv[])
{
	init();

	Camera* camera;
	camera = camera_init(-1000,1000,1);	
	camera_move(camera,(vec2){300,300});
	camera_use(camera);

	Sprite *sprite = create_sprite("images/player.png");

	while(!quit)
	{
		handle_input(&quit); //takes the quit variable to quit game when x is pressed
		
		move_ship();

		render_begin(); //shows a gray screen when nothing is rendered

		blit_sprite(sprite,(vec2){0,0},(vec2){200,200},(vec4){1,1,1,1});

		render_end();
	}
	free(sprite);
	free(camera);
	sprite = NULL;
	camera = NULL;
	return 0;
}

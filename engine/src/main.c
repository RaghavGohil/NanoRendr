#include<stdio.h>
#include<stdbool.h>
#define SDL_MAIN_HANDLED //define this!!!
#include "engine/global.h"

#pragma region CONFIG 

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600 

static bool quit = false;

#pragma endregion

#pragma region GAME

IVec2 ship_pos = {0,0};
IVec2 rotate_dir = {0,0};
IVec2 mouse_pos = {0,0};

#pragma endregion

void init()
{
	//ship:	
	ship_pos.x = SCREEN_WIDTH;
	ship_pos.y = SCREEN_HEIGHT;

	//engine:	
	render_init(SCREEN_WIDTH,SCREEN_HEIGHT,"Space Odyssey");	
}

void move_ship()
{
	mouse_pos = global.input.mouse_pos;
	rotate_dir.x = ship_pos.x - mouse_pos.x;
	rotate_dir.y = ship_pos.y - mouse_pos.y;
}

int main(int argc,char* argv[])
{
	init();

	while(!quit)
	{
		handle_input(&quit); //takes the quit variable to quit game when x is pressed
		
		move_ship();

		render_begin(); //shows a gray screen when nothing is rendered

		render_quad
		(
			(vec2) {SCREEN_WIDTH/2,SCREEN_HEIGHT/2},
			(vec2) {50,50},
			(vec4) {0.4,0.8,0.2,1}
		);
		render_quad
		(
			(vec2) {mouse_pos.x,mouse_pos.y},
			(vec2) {20,20},
			(vec4) {0.7,0.8,1,1}
		);
		render_quad
		(
			(vec2) {rotate_dir.x,rotate_dir.y},
			(vec2) {20,20},
			(vec4) {1,0.2,0.2,1}
		);

		render_end();
	}
	return 0;
}

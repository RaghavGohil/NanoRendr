#include<stdio.h>
#include<stdbool.h>
#define SDL_MAIN_HANDLED //define this!!!
#include "engine/global.h"

#pragma region CONFIG 

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600 

static bool quit = false;

#pragma endregion

int main(int argc,char* argv[])
{
	render_init(SCREEN_WIDTH,SCREEN_HEIGHT,"My Game");	

	while(!quit)
	{
		handle_input(&quit); //takes the quit variable to quit game when x is pressed
		
		//computation funcs go here:

		render_begin(); //shows a gray screen when nothing is rendered

		//render funcs go here:

		IVec2 mouse_pos = global.input.mouse_pos;
		printf("%d,%d\n",mouse_pos.x,mouse_pos.y);
		render_quad
		(
			(vec2) {SCREEN_WIDTH/2,SCREEN_HEIGHT/2},
			(vec2) {50,50},
			(vec4) {0.4,0.8,0.2,1}
		);

		render_end();
	}
	return 0;
}

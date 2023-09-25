#include<stdio.h>
#include<stdbool.h>
#define SDL_MAIN_HANDLED //define this!!!
#include "engine/global.h"

int main(int argc,char* argv[])
{
	render_init(800,600,"My Game");	
	
	bool quit = false;

	while(!quit)
	{
		handle_input(&quit); //takes the quit variable to quit game when x is pressed
		render_begin(); //shows a gray screen when nothing is rendered

		IVec2 mouse_pos = get_mouse_pos();
		printf("%d,%d\n",mouse_pos.x,mouse_pos.y);
		render_quad
		(
			(vec2) {global.render.width*0.5,global.render.height*0.5},
       			(vec2) {50,50},
			(vec4) {1,1,1,1}
		);

		render_end();
	}
	return 0;
}

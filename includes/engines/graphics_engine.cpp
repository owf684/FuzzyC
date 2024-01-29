/* Name of Program: graphics_engine
*
*  Purpose: This loads and renders all the 
*  sprites in the render buffer
*  
*  Author: Christopher Corona
*
*  Version: v0.1.0
*
*  Assumption: None
*
*  Things to do: 
*  Create load_render_buffer function
*
*/

#include "graphics_engine.h"



// Constructor
GraphicsEngine::GraphicsEngine(int input_width,int input_height, int input_bpp)
{
	// set dimensions
	width = input_width;
	height = input_height;
	bpp = input_bpp;
	
	
	// initialize sdl
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		std::cerr << "Error Initializing SDL: " << SDL_GetError() << std::endl;
	} 
		
	window = SDL_CreateWindow("Fuzzy C",
							SDL_WINDOWPOS_CENTERED,
							SDL_WINDOWPOS_CENTERED,
							width, height,
							SDL_WINDOW_SHOWN);

	if (!window) {std::cerr << "Failed to Create Window\n";}

	SDL_UpdateWindowSurface(window);

    //SDL_WM_SetCaption("FuzzyC", NULL);

}

/* Function: update()
*
*  Purpose: loads and renders all objects in the render_buffer
*/

void GraphicsEngine::update()
{
	/*
	SDL_FillRect(screen,0,0);

	for(int i = 0; i < render_buffer.size(); i++)
	{
		SDL_BlitSurface(render_buffer[i]->sprite.current,NULL,screen,&render_buffer[i]->sprite.rect);

	}

	SDL_Flip(screen);

	*/
	SDL_UpdateWindowSurface(window);

}




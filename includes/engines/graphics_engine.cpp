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
#include "engine_globals.h"
#include "interface_globals.h"

// Constructor
GraphicsEngine::GraphicsEngine(int input_width,int input_height, int input_bpp)
{
	// set dimensions
	width = input_width;
	height = input_height;
	bpp = input_bpp;
	
	
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_CreateWindowAndRenderer(width, height, SDL_WINDOW_RESIZABLE, &window, &renderer);
	SDL_SetWindowPosition(window,0,0);
    SDL_RenderClear(renderer);
    SDL_RenderPresent(renderer);
	grid_size = 32;

}

/* Function: update()
*
*  Purpose: loads and renders all objects in the render_buffer
*/

void GraphicsEngine::update()
{

	SDL_SetRenderDrawColor(renderer, (Uint8)(scene_color.x * 255), (Uint8)(scene_color.y * 255), (Uint8)(scene_color.z * 255), (Uint8)(scene_color.w * 255));;
    SDL_RenderClear(renderer);
	
	if (engine_interface.view_grid) draw_grid();

	for (int i = 0; i < render_buffer.size(); i++) {

    	// Convert the surface to a texture
    	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, render_buffer[i]->sprite.current);

    	// Check if the conversion was successful
    	if (texture != nullptr) {

        	// Copy the texture to the renderer
       		SDL_RenderCopy(renderer, texture, nullptr, &render_buffer[i]->sprite.rect);

        	// Free the texture (you can do this after rendering)
        	SDL_DestroyTexture(texture);
   	 	}
	}

	engine_interface.update();
	
	SDL_RenderPresent(renderer);

}


void GraphicsEngine::draw_grid() {
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // Set color to white
    // Draw vertical lines
    for (int x = 0; x <= width; x += grid_size) {
        SDL_RenderDrawLine(renderer, x, 0, x, height);
    }
    // Draw horizontal lines
    for (int y = 0; y <=height; y += grid_size) {
        SDL_RenderDrawLine(renderer, 0, y, width, y);
    }
}





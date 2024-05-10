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


/* Function: update()
*
*  Purpose: loads and renders all objects in the render_buffer
*/

void GraphicsEngine::update()
{

	SDL_SetRenderDrawColor(renderer, (Uint8)(scene_color.x * 255), (Uint8)(scene_color.y * 255), (Uint8)(scene_color.z * 255), (Uint8)(scene_color.w * 255));;
    SDL_RenderClear(renderer);
	
	if (engine_interface.view_grid) draw_grid();

	for (auto& object_locator : render_buffer) {

		GameObject* objects = object_locator.item;
    	// Convert the surface to a texture
    	//SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, objects->sprite.current);

    	// Check if the conversion was successful
    	if (objects->sprite.current_texture != nullptr) {

        	// Copy the texture to the renderer
       		SDL_RenderCopy(renderer, objects->sprite.current_texture, nullptr, &objects->sprite.rect);

        	// Free the texture (you can do this after rendering)
        	//SDL_DestroyTexture(texture);
   	 	}
	}

	engine_interface.update();
	
	SDL_RenderPresent(renderer);

}


void GraphicsEngine::draw_grid() {
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // Set color to white

	// draws horizontal grid lines above 0 
	for (int x =0; x <= width-scroll_engine.accumulated_x; x += grid_size) {
        SDL_RenderDrawLine(renderer, x+scroll_engine.accumulated_x, 0, x+scroll_engine.accumulated_x, height);
    }

	
	// draws horizontal grid lines below 0
	for (int x =0; x <= width+scroll_engine.accumulated_x; x += grid_size) {
        SDL_RenderDrawLine(renderer, scroll_engine.accumulated_x - x, 0, scroll_engine.accumulated_x-x, height);
	}
	
	
    // draws vertical grid lines below 
    for (int y = 0; y <=height-scroll_engine.accumulated_y; y += grid_size) {
        SDL_RenderDrawLine(renderer, 0, y+scroll_engine.accumulated_y, width, y+scroll_engine.accumulated_y);
    }

	// draws vertical grid lines above
	for (int y = 0; y <=height+scroll_engine.accumulated_y; y += grid_size) {
        SDL_RenderDrawLine(renderer, 0, scroll_engine.accumulated_y-y, width, scroll_engine.accumulated_y-y);
    }

}


bool GraphicsEngine::contain(GameObject* object)
{
	if (object == nullptr) return false;
	return (object->physics.position.x + object->getWidth() > 0 && object->physics.position.x < width && 
		object->physics.position.y  > 0 && object->physics.position.y  < height );
}


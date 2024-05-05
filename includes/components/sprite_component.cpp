/* Name of Program: sprite_component
*
* Purpose: this provides tools for 
* loading and position, and animation 
* sprites
*
* Author: Christopher Corona
*
* Version: v0.1.0
*
* Assumptions:
* All images need to be BMP
*
* Things left to do:
* [1] Need to create animation tools
* like sprite sheet slicing
*
*  [2] Need to find a way to use other
*  formats of images
*/

#include "sprite_component.h"
#include "engine_globals.h"


// Constructor: No Arguments
Sprite::Sprite()
{ position.x = 0;
  position.y = 0;
  rect.x =0; rect.y=0; rect.w=50;rect.h=50;
}

// Destructor
Sprite::~Sprite()
{
 if (current != nullptr) {
        SDL_FreeSurface(current);
        current = nullptr;
    }
    if (current_texture != nullptr) {
        SDL_DestroyTexture(current_texture);
        current_texture = nullptr;
    }
}

// Constructor: Position Arguments
Sprite::Sprite(float input_x, float input_y){
	
	position.x = input_x;
	position.y = input_y;
	rect.x=position.x; rect.y=position.y; rect.w=0; rect.h=0; 
}

/* Function: set_current()
*
*  Purpose: This function 
*  sets the current sprite
*  with what ever image is 
*  given in the path
*
*  Input Limits: image_path 
*  needs to be a valid path.
*  If not invalid_path error()
*  will be thrown
* 
*  Things to do: implement that error
*/

void Sprite::set_current(char* image_path)
{

	current = SDL_LoadBMP(image_path);
	rect.w = current->w;
	rect.h = current->h;
	current_texture = SDL_CreateTextureFromSurface(graphics_engine.renderer, current);



}

/* Function: set_position()
*
* Purpose: This sets the position of the
* sprite
*
*/

void Sprite::set_position(float x_in, float y_in)
{
	position.x = x_in;
	position.y = y_in;
	rect.x=position.x; rect.y=position.y; 
}

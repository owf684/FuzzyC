/* Name of Program: input_engine
*
* Purpose: This monitors SDL events
* and packs relavant data to into structs
*
* Author: Chrsitopher Corona
*
* Version: v0.1.0
*
* TODO: 
* setup inputs for awsd
* setup inputs for other sdl events like minimization
*
*/

#include "input_engine.h"
#include "iostream"
using namespace std;



// Constructor
InputEngine::InputEngine()
{
quit = false;
}

/* Name of Function: get_keydown_event()
*
* Purpose: This function is called when 
* a keydown event occurs. It evaluates
* the keypress and updates the input structs accordingly
*
*/

void InputEngine::get_keydown_event(SDL_Keycode key_code)
{

	// set arrow keys
	switch (key_code)
	{
		case SDLK_UP:
			arrow_keys.up = true;
			break;

		case SDLK_DOWN:
			arrow_keys.down = true;
			break;

		case SDLK_RIGHT:
			arrow_keys.right = true;
			break;
		case SDLK_LEFT:
			arrow_keys.left = true;
			break;


	}


}

/* Name of Function: get_keyup_event()
*
* Purpose: This function is called when
* a keyup event occurs. It updates the
* input structs accordingly
*
*/

void InputEngine::get_keyup_event(SDL_Keycode key_code)
{

	// unset arrow keys
	switch(key_code)
	{
		case SDLK_UP:
			arrow_keys.up = false;
			break;
		case SDLK_DOWN:
			arrow_keys.down = false;
			break;
		case SDLK_RIGHT:
			arrow_keys.right = false;
			break;
		case SDLK_LEFT:
			arrow_keys.left = false;
			break;

	}

}

/* Name of function: update()
*
* Purpose: This function 
* updates the input structs
* by calling keydown and keyup
* event functions. It does
* this my polling for SDL events
*/

void InputEngine::update()
{
	SDL_PollEvent(&events);
	switch(events.type)
	{
		case SDL_KEYDOWN:
			get_keydown_event(events.key.keysym.sym);
			break;
		case SDL_KEYUP:
			get_keyup_event(events.key.keysym.sym);
			break;

		case SDL_QUIT:
			quit = true;
			break;
	}

}

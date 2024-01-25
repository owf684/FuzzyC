#ifndef INPUT_ENGINE_H
#define INPUT_ENGINE_H
#include <SDL/SDL.h>



class InputEngine{

	public:
	// constructor
	InputEngine();

	// input variables
	struct{
	bool up;
	bool down;
	bool left;
	bool right;
	} arrow_keys;
	struct {
	bool a;
	bool w;
	bool s; 
	bool d;
	} awsd;

	bool quit;
	

	SDL_Event events;

	// getters
	void get_keydown_event(SDLKey key_code);
	void get_keyup_event(SDLKey key_code);

	//
	void update();

};


#endif

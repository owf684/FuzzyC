#ifndef SPRITE_COMPONENT_H
#define SPRITE_COMPONENT_H

#include <SDL2/SDL.h>
#include <vector>
#include <string>


class Sprite{
public:
	Sprite();
	~Sprite();
	Sprite(float input_x, float input_y); 
	SDL_Surface *current;
	SDL_Texture* current_texture;
	std::vector<SDL_Surface>* sprite_sheet;
	bool has_sprite_sheet;
	SDL_Rect rect;
	struct {
	float x;
	float y;
	} position;
	

	// setters
	void set_current(char* image_path);
	void set_position(float x_in, float y_in);
};

#endif

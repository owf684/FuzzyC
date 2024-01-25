#pragma once
#ifndef GRAPHICS_ENGINE_H
#define GRAPHICS_ENGINE_H

#include <SDL/SDL.h>
#include <iostream>
#include <vector>
#include <memory>

// custom libraries
#include "../objects/game_object.h"




class GraphicsEngine
{
public: // Constructor 
	GraphicsEngine(int input_width, int input_height, int input_bpp);

	int width;
	int height;
	int bpp;
	SDL_Surface* screen;
	
	std::vector<std::unique_ptr <GameObject> > render_buffer;

	void update();	
};



#endif 

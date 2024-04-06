#pragma once
#ifndef GRAPHICS_ENGINE_H
#define GRAPHICS_ENGINE_H

#include <SDL2/SDL.h>
#include <iostream>
#include <vector>
#include <memory>
#include "game_object.h"
// custom libraries



class GraphicsEngine
{
public: // Constructor 
	GraphicsEngine(int input_width, int input_height, int input_bpp);
	void draw_grid();
	int width;
	int height;
	int grid_size;
	int bpp;
	SDL_Surface* screen;
	SDL_Window* window; 
	SDL_Renderer* renderer;
	
	
	std::vector<std::unique_ptr <GameObject> > render_buffer;

	void update();	
};



#endif 

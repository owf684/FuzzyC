#pragma once
#ifndef GRAPHICS_ENGINE_H
#define GRAPHICS_ENGINE_H

#include <SDL2/SDL.h>
#include <iostream>
#include <vector>
#include <memory>
#include "game_object.h"
#include "quad_tree.h"
// custom libraries



class GraphicsEngine
{
public: // Constructor 
	GraphicsEngine(int input_width,int input_height, int input_bpp) : render_buffer(Point(0,0),Point(input_width, input_height))
	{
	// set dimensions
	width = input_width;
	height = input_height;
	bpp = input_bpp;
	
	
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_CreateWindowAndRenderer(width, height, SDL_WINDOW_FULLSCREEN_DESKTOP, &window, &renderer);
	SDL_SetWindowPosition(window,0,0);
	SDL_SetWindowResizable(window, SDL_TRUE);
    SDL_RenderClear(renderer);
    SDL_RenderPresent(renderer);
	grid_size = 32;

	}
	void draw_grid();
	int width;
	int height;
	int grid_size;
	int bpp;
	SDL_Surface* screen;
	SDL_Window* window; 
	SDL_Renderer* renderer;
	
	
	//std::vector<std::unique_ptr <GameObject> > render_buffer;
	QuadTreeContainer<GameObject* > render_buffer;

	void update();	
};



#endif 

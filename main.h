#pragma once
#ifndef MAIN_H
#define MAIN_H

#include "./includes/objects/game_object.h"
#include "./includes/engine_globals.h"
#include "./game_data/objects/bird.h"
#include "./game_data/objects/test_platform.h"
#include <ctime>
#include <unistd.h>
#include <iostream>
#include <chrono>
#include <thread>
#include <cmath>
#include <SDL2/SDL.h>
#include <vector>
#include "interface_globals.h"
#include <string>
#include <qadon.h>
//#include "./includes/objects/rdoh.h"
//#include "./includes/objects/rdoh_util.h"


/* Initialize Interface Globals
*
*/

// Engine Interface Variables
bool play_pause = false;


// Scene Editor Variables
ImVec4 	scene_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);


// Object Editor Variables
bool add_object_menu_active = false;
char object_name[128] = "";
std::vector <std::string> asset_list = {};
int sprite_name_index =0;
int last_selected_sprite_index = 0;
int selected_asset_index = 0;
int draw_layer_index = 0;
std::string selected_sprite[5] {"None","None","None","None","None"};
qadon object_data;
bool object_save_button_active = false;


/* Engine Globals
*
*/
std::map<std::string,std::any> objects_library;

// Frame Rate Variables
float dt = 0;
float frames_per_second_f = 120.0;
const float micro_seconds_f = pow(10,6); // == 1 / micro_seconds
const float frame_duration_f = (1.0 / frames_per_second_f)*micro_seconds_f;
float time_elapsed_f = 0.0;


// Engines Variables
GraphicsEngine graphics_engine(1440,900,32);
InputEngine input_engine;
SpriteEngine sprite_engine;
PhysicsEngine physics_engine;
CollisionEngine collision_engine;
EngineInterface engine_interface;
ScrollEngine scroll_engine; 
CameraEngine camera_engine;
// Object variables
RDOH object_handler;
RdohUtil object_util;


#endif 

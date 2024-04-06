
#pragma once
#ifndef GLOBALS_H
#define GLOBALS_H 

#include "imgui.h"
#include "imgui_impl_sdl2.h"
#include "imgui_impl_sdlrenderer2.h"
#include <vector>
#include <string>
#include <qadon.h>


// Engine Interface Globals

extern bool play_pause;
extern float frames_per_second_f;



// Object Editor Globals

extern bool add_object_menu_active;
extern char object_name[128];


// Scene Editor Globals

extern ImVec4 scene_color;
extern std::vector<std::string> asset_list;
extern int selected_asset_index;
extern int sprite_name_index;
extern int last_selected_sprite_index;
extern int draw_layer_index;
extern qadon object_data;
extern std::string selected_sprite[5];
extern bool object_save_button_active;
#endif
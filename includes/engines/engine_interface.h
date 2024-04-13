#pragma once
#ifndef ENGINE_INTERFACE_H
#define ENGINE_INTERFACE_H
#include <vector>
#include <string>
#include <filesystem>
#include <qadon.h>
class EngineInterface {

    public: 
        EngineInterface();
        void update();
        void main_menu();
        void engine_controls();
        void object_contorls();
        void scene_controls();
        void camera_controls();
        void object_view_inteface();
        void add_object_menu();
        // bools 
        bool show_add_object_menu;
        bool place_object_enabled;
        bool erase_object_enabled;
        bool already_placed; 
        bool view_grid;
        bool move_world_enabled;
        bool set_to_zero;
        bool select_follow_object;
        bool snap_to_grid;
        // ints
        int move_speed;

        struct  {
            char object_name[256];
            int draw_layer_index;
            std::vector<std::string> available_assets;
            const char* default_sprite;
        }object_info;

        const char* selected_object;

    
};
#endif
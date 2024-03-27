#pragma once
#ifndef ENGINE_INTERFACE_H
#define ENGINE_INTERFACE_H
#include <vector>
#include <string>
#include <filesystem>

class EngineInterface {

    public: 
        EngineInterface();
        void update();
        void main_menu();
        void engine_controls();
        void object_contorls();
        void scene_controls();
        void object_view_inteface();
        void add_object_menu();
        // bools 
        bool show_add_object_menu;

        struct  {
            char object_name[256];
            int draw_layer_index;
            std::vector<std::string> available_assets;
            const char* defaut_sprite;
        }object_info;
    
};
#endif
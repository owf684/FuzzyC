#pragma once
#ifndef RDOH_H
#define RDOH_H
#include <map>
#include <any>
#include <string>
#include "imgui.h"
//custom objects

class RDOH 
{
    public:

        std::map<std::string, std::any> object_library;
        void add_object(std::string object_name);
        void remove_object(std::string object_name);
        void init_objects();
        void generate_object(std::string object_name, ImVec2 mouse_position);


};


#endif
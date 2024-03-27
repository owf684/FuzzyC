#pragma once
#ifndef OBJECT_HANDLER_H
#define OBJECT_HANDLER_H
#include <iostream>
#include <dlfcn.h> // For dynamic loading on Unix-like systems
#include "game_object.h"
#include "vector"
#include "map"
#include <string>

class ObjectHandler {

    public:
        // unload all libraries
        ~ObjectHandler()
        {
             for(const auto& pair: object_libs)
            {
                dlclose(pair.second);
                std::cout << "closing lib: " << pair.first << " : " << pair.second << std::endl;

            }
        }

        int load_object_library(std::string object_name,const char* object_library){
            void* object_library_handle = dlopen(object_library,RTLD_LAZY);
    
            if (object_library_handle == nullptr) {
            std::cerr << "Failed to load library: " << dlerror() << std::endl;
            return 1;
            }

            object_libs[object_name] = object_library_handle;
            return 0;
        }

        int remove_object_library(std::string object_name)
        {
            // make sure library exists before removing
            if (object_libs[object_name] != NULL)
            {
                dlclose(object_libs[object_name]);
                object_libs.erase(object_name);
            } else {

                // ensure to erase failed object_name. simply trying to access a map with a non existent key 
                // creates a new entry in the map
                object_libs.erase(object_name);
                std::cerr << "could not remove object_library. not found in object_libs \n";
            }
            return 0; 
        }

        std::unique_ptr<GameObject> call_generate_object( std::string object_name)
        {
            typedef std::unique_ptr<GameObject> (*GenerateObject)();
            GenerateObject call_generate_object = (GenerateObject)dlsym(object_libs[object_name], "generate_object");
            if (call_generate_object != nullptr) {

                return call_generate_object();

            } else {
                std::cerr << "Failed to find symbol 'generate_object' in the library for " << object_name << std::endl;
                return nullptr;
            }

        }

    private:

        std::map<std::string,void*> object_libs;


};




#endif


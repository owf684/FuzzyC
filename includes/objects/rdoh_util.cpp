
#include "rdoh_util.h"

std::string strupper(std::string word)
{
    std::string temp = "";
    for(char&characters : word)
    {
     temp += toupper(characters);
    }
    return temp;

}

void RdohUtil::init(std::string exe_dir)
{   obj_lib.clear();
    qadon q_obj_lib( exe_dir + "/includes/objects/object_library.qadon");
	for (auto& pair : q_obj_lib)
	{
		obj_lib.push_back(pair.second);
	}
}

void RdohUtil::write_rdoh()
{
    std::ofstream rdoh_cpp(rdoh_file_path);
    qadon obj_lib(object_lib_path);
    create_headers(rdoh_cpp,obj_lib);
    create_init_objects(rdoh_cpp, obj_lib);
    create_generate_object(rdoh_cpp,obj_lib);
    rdoh_cpp.close();
}

void RdohUtil::add_object(std::string object_name)
{
    std::ofstream rdoh_cpp(rdoh_file_path);
    qadon obj_lib(object_lib_path);
    obj_lib[object_name] = object_name;
    obj_lib.write(object_lib_path);
    create_headers(rdoh_cpp,obj_lib);
    create_init_objects(rdoh_cpp, obj_lib);
    create_update_object(rdoh_cpp,obj_lib);
    create_generate_object(rdoh_cpp,obj_lib);
    rdoh_cpp.close();
    
}

void RdohUtil::remove_object(std::string object_name)
{
    std::ofstream rdoh_cpp(rdoh_file_path);
    qadon obj_lib(object_lib_path);
    obj_lib.remove(object_name);
    obj_lib.write(object_lib_path);
    create_headers(rdoh_cpp,obj_lib);
    create_init_objects(rdoh_cpp, obj_lib);
    create_update_object(rdoh_cpp,obj_lib);
    create_generate_object(rdoh_cpp,obj_lib);

    rdoh_cpp.close();
    std::string command_1 = "rm ./game_data/objects/"+object_name+".cpp";
    const char* sys_command_1 = command_1.c_str();
    std::string command_2 = "rm ./game_data/objects/"+object_name+".h";
    const char* sys_command_2 = command_2.c_str();
        std::string command_3 = "rm ./game_data/objects/"+object_name+".o";
    const char* sys_command_3 = command_3.c_str();
    system(sys_command_1);
    system(sys_command_2);
    system(sys_command_3);

}

void RdohUtil::set_rdoh_file_path(std::string file_path)
{
    rdoh_file_path = file_path;
}

void RdohUtil::set_object_lib_path(std::string file_path)
{
    object_lib_path = file_path;
}

void RdohUtil::create_object_files(std::string object_name, std::string current_sprite_file_path)
{
    // create header file
    std::ofstream new_header("./game_data/objects/"+object_name+".h");
    std::string object_name_upper = strupper(object_name);

    new_header << "#ifndef " + object_name_upper +"_H \n"; // change to object name
    new_header << "#define " + object_name_upper +"_H\n" ; 
    new_header << "#include " + std::string(1,'"') + "engine_globals.h" + std::string(1,'"') +  "\n\n\n";

    new_header << "class  " + object_name + ": public GameObject \n{ \n";
    new_header << "\tpublic:\n";
    new_header << "\t\t" + object_name + "();\n\n";
    new_header << "\t\tvoid update() override;\n\n";
    new_header << "};\n";
    new_header << "#endif\n";

    new_header.close();

    // create cpp file
    std::ofstream new_cpp("./game_data/objects/"+object_name+".cpp");
    new_cpp << "#include "+ std::string(1,'"') + object_name +".h"+ std::string(1,'"') + "\n";
    new_cpp << "#include "+ std::string(1,'"') + "iostream" + std::string(1,'"') + "\n";
    new_cpp << "using namespace std;\n\n\n";
   
    new_cpp << object_name + "::" + object_name + "()\n{\n"; 
    new_cpp << "\tsprite.set_current(" + std::string(1,'"') + current_sprite_file_path + std::string(1,'"') + "); \n";
    new_cpp << "\tphysics.gravity = 980;\n";
    new_cpp <<	"\tcollider.detect_collisions = true;\n}\n\n";
    new_cpp << "\tvoid " + object_name  + "::update()\n{\n\n\n}";
    new_cpp.close();


}

void RdohUtil::create_headers(std::ofstream &rdoh_file, qadon object_library)
{
    std::string apo = std::string(1,'"');
    rdoh_file << "#include " + std::string(1,'"') + "rdoh.h" + std::string(1,'"') + "\n";
    rdoh_file << "#include " + std::string(1,'"') + "engine_globals.h" + std::string(1,'"') + "\n";
    for(const auto& pair : object_library)   
    {
        rdoh_file << "#include " + std::string(1,'"') + pair.second + ".h" + std::string(1,'"') + "\n";

    }
    rdoh_file << "\n\n\n";
}

void RdohUtil::create_init_objects(std::ofstream &rdoh_file, qadon object_library)
{
    rdoh_file << "void RDOH::init_objects() \n { \n";
    for (const auto& pair : object_library)
    {
        rdoh_file << "\t object_library[" + std::string(1,'"') + pair.second + std::string(1,'"') + "] = " + pair.second + "(); \n";
    }
    rdoh_file << "} \n\n\n";
}


void RdohUtil::create_generate_object(std::ofstream &rdoh_file, qadon object_library)
{
    /*
    	if (object_name == "warp_pipe") { 
		GameObject* new_object = new warp_pipe();
		new_object->object_name = object_name;
		new_object->set_position(mouse_position.x,mouse_position.y);
		update_object(new_object,camera_active);
		 graphics_engine.render_buffer.insert(new_object); 
	    }
    
    */
    rdoh_file << "void RDOH::generate_object(std::string object_name, ImVec2 mouse_position, bool camera_active) {\n\n";
    for (auto&pair : object_library)
    {
        rdoh_file << "\tif (object_name == "+ std::string(1,'"') + pair.second + std::string(1,'"') +") { \n";
        rdoh_file << "\t\tGameObject* new_object = new " + pair.second  + "(); \n";
        rdoh_file << "\t\tnew_object->object_name = object_name;\n";
        rdoh_file << "\t\tnew_object->set_position(mouse_position.x,mouse_position.y);\n";
        rdoh_file << "\t\tupdate_object(new_object,camera_active);\n";
        rdoh_file << "\t\tgraphics_engine.render_buffer.insert(new_object);\n";
        rdoh_file << "\t}\n\n";
    }
    rdoh_file << "}\n";
    
}

    void RdohUtil::create_update_object(std::ofstream &rdoh_file, qadon object_library)
    {
     
        rdoh_file << "void update_object(GameObject* object, bool camera_active)\n";
        rdoh_file << "{\n";
	    rdoh_file << "\tphysics_engine.update(object);\n";
	    rdoh_file << "\tsprite_engine.update(object);\n";
	    rdoh_file << "\tobject->camera.camera_active = camera_active;\n";
        rdoh_file << "\treturn;\n";
        rdoh_file << "}\n\n\n";
     
    }



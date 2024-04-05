#include "rdoh.h"
#include "engine_globals.h"
#include "bird.h"
#include "Chris.h"



void RDOH::init_objects() 
 { 
	 object_library["bird"] = bird(); 
	 object_library["Chris"] = Chris(); 
} 


void RDOH::generate_object(std::string object_name, ImVec2 mouse_position) {

	if (object_name == "bird") { 
		bird anyObj = std::any_cast<bird>(object_library["bird"]); 
		 graphics_engine.render_buffer.push_back(std::move(anyObj.generate_object())); 
		 graphics_engine.render_buffer[graphics_engine.render_buffer.size()-1]->set_position(mouse_position.x,mouse_position.y);
	}

	if (object_name == "Chris") { 
		Chris anyObj = std::any_cast<Chris>(object_library["Chris"]); 
		 graphics_engine.render_buffer.push_back(std::move(anyObj.generate_object())); 
		 graphics_engine.render_buffer[graphics_engine.render_buffer.size()-1]->set_position(mouse_position.x,mouse_position.y);
	}

	auto object = std::move(graphics_engine.render_buffer.back());
	graphics_engine.render_buffer.pop_back();
	physics_engine.update(object);
	collision_engine.update(object);
	sprite_engine.update(object);
	std::vector< std::unique_ptr<GameObject> >::iterator it;
	it = graphics_engine.render_buffer.begin();
	graphics_engine.render_buffer.insert(it, std::move(object));
}

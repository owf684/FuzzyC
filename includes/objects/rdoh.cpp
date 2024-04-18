#include "rdoh.h"
#include "engine_globals.h"
#include "warp_pipe.h"
#include "mario.h"
#include "brick.h"
#include "bird.h"
#include "test_platform.h"
#include "breakable_brick.h"



void RDOH::init_objects() 
 { 
	 object_library["warp_pipe"] = warp_pipe(); 
	 object_library["mario"] = mario(); 
	 object_library["brick"] = brick(); 
	 object_library["bird"] = bird(); 
	 object_library["test_platform"] = test_platform(); 
	 object_library["breakable_brick"] = breakable_brick(); 
} 


void RDOH::generate_object(std::string object_name, ImVec2 mouse_position, bool camera_active) {

	if (object_name == "warp_pipe") { 
		warp_pipe anyObj = std::any_cast<warp_pipe>(object_library["warp_pipe"]); 
		 graphics_engine.render_buffer.push_back(std::move(anyObj.generate_object())); 
		 graphics_engine.render_buffer[graphics_engine.render_buffer.size()-1]->set_position(mouse_position.x,mouse_position.y);
	}

	if (object_name == "mario") { 
		mario anyObj = std::any_cast<mario>(object_library["mario"]); 
		 graphics_engine.render_buffer.push_back(std::move(anyObj.generate_object())); 
		 graphics_engine.render_buffer[graphics_engine.render_buffer.size()-1]->set_position(mouse_position.x,mouse_position.y);
	}

	if (object_name == "brick") { 
		brick anyObj = std::any_cast<brick>(object_library["brick"]); 
		 graphics_engine.render_buffer.push_back(std::move(anyObj.generate_object())); 
		 graphics_engine.render_buffer[graphics_engine.render_buffer.size()-1]->set_position(mouse_position.x,mouse_position.y);
	}

	if (object_name == "bird") { 
		bird anyObj = std::any_cast<bird>(object_library["bird"]); 
		 graphics_engine.render_buffer.push_back(std::move(anyObj.generate_object())); 
		 graphics_engine.render_buffer[graphics_engine.render_buffer.size()-1]->set_position(mouse_position.x,mouse_position.y);
	}

	if (object_name == "test_platform") { 
		test_platform anyObj = std::any_cast<test_platform>(object_library["test_platform"]); 
		 graphics_engine.render_buffer.push_back(std::move(anyObj.generate_object())); 
		 graphics_engine.render_buffer[graphics_engine.render_buffer.size()-1]->set_position(mouse_position.x,mouse_position.y);
	}

	if (object_name == "breakable_brick") { 
		breakable_brick anyObj = std::any_cast<breakable_brick>(object_library["breakable_brick"]); 
		 graphics_engine.render_buffer.push_back(std::move(anyObj.generate_object())); 
		 graphics_engine.render_buffer[graphics_engine.render_buffer.size()-1]->set_position(mouse_position.x,mouse_position.y);
	}

	graphics_engine.render_buffer[graphics_engine.render_buffer.size()-1]->object_name = object_name;
	auto object = std::move(graphics_engine.render_buffer.back());
	graphics_engine.render_buffer.pop_back();
	physics_engine.update(object);
	collision_engine.update(object);
	sprite_engine.update(object);
	object->camera.camera_active = camera_active;
	std::vector< std::unique_ptr<GameObject> >::iterator it;
	it = graphics_engine.render_buffer.begin();
	graphics_engine.render_buffer.insert(it, std::move(object));
}

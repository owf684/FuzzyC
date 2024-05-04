#include "rdoh.h"
#include "engine_globals.h"
#include "warp_pipe.h"
#include "mario.h"
#include "brick.h"
#include "bird.h"
#include "test_platform.h"
#include "breakable_brick.h"

void update_object(GameObject* object, bool camera_active);


// I don't think i need init objects anymore!
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
		GameObject* new_object = new warp_pipe();
		new_object->set_position(mouse_position.x,mouse_position.y);
		update_object(new_object,camera_active);
		 graphics_engine.render_buffer.insert(new_object); 

	}
	
	if (object_name == "mario") { 
		GameObject* new_object = new mario();
		new_object->set_position(mouse_position.x,mouse_position.y);
		update_object(new_object,camera_active);
		graphics_engine.render_buffer.insert(new_object); 
	}

	if (object_name == "brick") { 
		GameObject* new_object = new brick();		
		new_object->set_position(mouse_position.x,mouse_position.y);
		update_object(new_object,camera_active);
		graphics_engine.render_buffer.insert(new_object); 
	}
	
	if (object_name == "bird") { 
		GameObject* new_object = new bird();
		new_object->set_position(mouse_position.x,mouse_position.y);
		update_object(new_object,camera_active);
		graphics_engine.render_buffer.insert(new_object); 
	}
	
	if (object_name == "test_platform") { 
		GameObject* new_object = new test_platform();
		new_object->set_position(mouse_position.x,mouse_position.y);
		update_object(new_object,camera_active);
		graphics_engine.render_buffer.insert(new_object); 
	}

	if (object_name == "breakable_brick") { 
		GameObject* new_object = new breakable_brick();
		new_object->set_position(mouse_position.x,mouse_position.y);
		update_object(new_object,camera_active);
		graphics_engine.render_buffer.insert(new_object); 
	}
	
}
	

void update_object(GameObject* object, bool camera_active)
{
	physics_engine.update(object);
	//collision_engine.update(object);
	sprite_engine.update(object);
	object->camera.camera_active = camera_active;
}
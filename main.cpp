#include "main.h"
#undef main
using namespace std::chrono;



int main(int argc, char* argv[])
{

// setup absolute paths
exe_path = fs::canonical(argv[0]);
exe_dir = exe_path.parent_path();
engine_interface.update_scenes_vector();

// setup object handler
object_handler.init_objects();

object_util.set_object_lib_path( exe_dir.string() + "/includes/objects/object_library.qadon");
object_util.set_rdoh_file_path( exe_dir.string() + "/includes/objects/rdoh.cpp");
object_util.init(exe_dir.string());

bool first_pass = true;

// main game loop 
while(!input_engine.quit)
{	
	auto dt_start = high_resolution_clock::now();	
	
	graphics_engine.update();
	input_engine.update();

	if (first_pass || play_pause)
	{
		// update all objects in render buffer
		for(auto object_locator = graphics_engine.render_buffer.begin(); object_locator != graphics_engine.render_buffer.end(); object_locator++)
		{			
			if (first_pass) first_pass = false;
			
			GameObject* object = object_locator->item;
						
			object->update();	

			
			if (graphics_engine.contain(object))
				physics_engine.update(object);		
			
			collision_engine.update(object);
			camera_engine.update(object);
			scroll_engine.update(object);
			sprite_engine.update(object);

			graphics_engine.render_buffer.reinsert(object_locator);
			
		} 
		
	} else if (!play_pause)
	{
		scroll_engine.move_world();
	}

	// update delta time step
	auto frame_rate = (1.0 / frames_per_second_f)*micro_seconds_f;

	if (frame_rate - dt >0)
		usleep(frame_rate - dt);

	auto dt_end = high_resolution_clock::now();
	auto dt_final = duration_cast<milliseconds>(dt_end - dt_start);
	dt = dt_final.count()/1000.0;
}
}

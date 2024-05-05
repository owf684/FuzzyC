#include "main.h"
#undef main
using namespace std::chrono;



int main(int argc, char* argv[])
{

exe_path = fs::canonical(argv[0]);
exe_dir = exe_path.parent_path();
engine_interface.update_scenes_vector();

bool first_pass = true;

object_handler.init_objects();

// lib path
object_util.set_object_lib_path( exe_dir.string() + "/includes/objects/object_library.qadon");
object_util.set_rdoh_file_path( exe_dir.string() + "/includes/objects/rdoh.cpp");
object_util.init(exe_dir.string());

// main game loop 
while(!input_engine.quit)
{	
	// capture current time
	auto dt_start = high_resolution_clock::now();	
	
	graphics_engine.update();
	input_engine.update();

	if (first_pass || play_pause)
	{
		// update all objects
		for(auto object = graphics_engine.render_buffer.begin(); object != graphics_engine.render_buffer.end(); object++)
		{	
			
			if ((*object) != nullptr)
			{
				(*object)->update();
			
				physics_engine.update(*object);
				std::list<GameObject*> other_objs;
				if ((*object)->collider.detect_collisions) graphics_engine.render_buffer.search(*object, other_objs);
				collision_engine.update(*object,other_objs);
				sprite_engine.update(*object);
				scroll_engine.update(*object);
				camera_engine.update(*object);

				graphics_engine.render_buffer.reinsert(object);
			}
			if (first_pass) first_pass = false;
		} 
	} else if (!play_pause)
	{
		scroll_engine.move_world();
	}

	// update delta time step
	usleep((1.0 / frames_per_second_f)*micro_seconds_f);
	auto dt_end = high_resolution_clock::now();
	auto dt_final = duration_cast<milliseconds>(dt_end - dt_start);
	dt = dt_final.count()/1000.0;
}
}

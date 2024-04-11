#include "main.h"
#undef main
using namespace std::chrono;



int main(int argc, char* argv[])
{

bool first_pass = true;

object_handler.init_objects();
object_util.set_object_lib_path("./includes/objects/object_library.qadon");
object_util.set_rdoh_file_path("./includes/objects/rdoh.cpp");
object_util.init();

std::unique_ptr<GameObject> object;

// main game loop 
while(!input_engine.quit)
{	
	// capture current time
	auto dt_start = high_resolution_clock::now();	
	
	graphics_engine.update();
	input_engine.update();

	if (first_pass || play_pause)
	{
		// update engines
		
		// update all objects
		for(int i =0; i < graphics_engine.render_buffer.size(); i++)
		{	
			// move out of buffer
			object = std::move(graphics_engine.render_buffer.back());
			graphics_engine.render_buffer.pop_back();

			// update object components
			object->update();
			physics_engine.update(object);
			collision_engine.update(object);
			sprite_engine.update(object);
			scroll_engine.update(object);
			camera_engine.update(object);
			// move back into buffer
  			std::vector< std::unique_ptr<GameObject> >::iterator it;
			it = graphics_engine.render_buffer.begin();
			graphics_engine.render_buffer.insert(it, std::move(object));

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

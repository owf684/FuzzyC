#include "main.h"
#include <thread>
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

// Initialize variables for timing
typedef std::chrono::high_resolution_clock Clock;
auto currentTime = Clock::now();
auto endTime = Clock::now();

// main game loop 
while(!input_engine.quit)
{	

	std::thread graphicsThread([&]() {
        graphics_engine.update();
    });
	//graphics_engine.update();

	input_engine.update();

    currentTime = Clock::now();

	if ( play_pause)
	{
		
		for(auto object_locator = graphics_engine.render_buffer.begin(); object_locator != graphics_engine.render_buffer.end(); object_locator++)
		{				
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

	endTime = Clock::now();

	std::chrono::nanoseconds duration = endTime - currentTime;
	long frame_rate_delay = ( (1.0/frames_per_second_f) - (duration.count() * 1e-9) ) * 1e9;
	if (frame_rate_delay > 0){
		std::this_thread::sleep_for(std::chrono::nanoseconds(frame_rate_delay));}
	else	{
		std::cout << "warning: frame rate delay is negative" << std::endl;}

	dt = 1 / frames_per_second_f;


	graphicsThread.join();

}
}

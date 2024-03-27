#include "main.h"
#undef main
using namespace std::chrono;



int main(int argc, char* argv[])
{


// creating a test game object
//bird_ptr->set_position(300,370);

// setting position ---> need function in gameobject that repositions all the components
platform_ptr->set_position(300,400);
platform_ptr->physics.pause = true;
platform_ptr->physics.mass = 100000;

platform_ptr_2->set_position(450,350);
platform_ptr_2->physics.pause = true;
platform_ptr_2->physics.mass = 100000;

platform_ptr_3->set_position(150,350);
platform_ptr_3->physics.pause = true;
platform_ptr_3->physics.mass = 100000;

platform_ptr_4->set_position(300,250);
platform_ptr_4->physics.pause = true;
platform_ptr_4->physics.mass = 100000;

// adding it to the render buffer
//graphics_engine.render_buffer.push_back(std::move(bird_ptr));
graphics_engine.render_buffer.push_back(std::move(platform_ptr));
graphics_engine.render_buffer.push_back(std::move(platform_ptr_2));
graphics_engine.render_buffer.push_back(std::move(platform_ptr_3));
graphics_engine.render_buffer.push_back(std::move(platform_ptr_4));

bool first_pass = true;

std::unique_ptr<GameObject> object;

//object_handler.load_object_library("bird" , "./game_data/lib/bird.so");

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
		//for(auto& object: graphics_e.render_buffer)
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

			// move back into buffer
  			std::vector< std::unique_ptr<GameObject> >::iterator it;
			it = graphics_engine.render_buffer.begin();
			graphics_engine.render_buffer.insert(it, std::move(object));

			if (first_pass) first_pass = false;
		}
	}


	// update delta time step
	usleep((1.0 / frames_per_second_f)*micro_seconds_f);
	auto dt_end = high_resolution_clock::now();
	auto dt_final = duration_cast<milliseconds>(dt_end - dt_start);
	dt = dt_final.count()/1000.0;
}
}

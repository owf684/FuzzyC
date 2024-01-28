#include "main.h"
#undef main
using namespace std::chrono;



int main(int argc, char* argv[])
{


// creating a test game object
bird_ptr->set_position(300,370);

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
graphics_e.render_buffer.push_back(std::move(bird_ptr));
graphics_e.render_buffer.push_back(std::move(platform_ptr));
graphics_e.render_buffer.push_back(std::move(platform_ptr_2));
graphics_e.render_buffer.push_back(std::move(platform_ptr_3));
graphics_e.render_buffer.push_back(std::move(platform_ptr_4));


std::unique_ptr<GameObject> object;

// main game loop 
while(!input_e.quit)
{	
	// capture current time
	auto dt_start = high_resolution_clock::now();
	
	// update engines
	input_e.update();
	graphics_e.update();

	// update all objects
	//for(auto& object: graphics_e.render_buffer)
	for(int i =0; i < graphics_e.render_buffer.size(); i++)
	{	
		// move out of buffer
		object = std::move(graphics_e.render_buffer.back());
		graphics_e.render_buffer.pop_back();

		// update object components
		object->update(input_e);
		physics_e.update(object, input_e, dt_f);
		collision_e.update(object, graphics_e.render_buffer,input_e);
		sprite_e.update(object);

		// move back into buffer
  		std::vector< std::unique_ptr<GameObject> >::iterator it;
		it = graphics_e.render_buffer.begin();
		graphics_e.render_buffer.insert(it, std::move(object));

	}

	// update delta time step
	usleep(frame_duration_f);
	auto dt_end = high_resolution_clock::now();
	auto dt_final = duration_cast<milliseconds>(dt_end - dt_start);
	dt_f = dt_final.count()/1000.0;
}
}

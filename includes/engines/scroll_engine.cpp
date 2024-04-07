#include "scroll_engine.h"
#include "engine_globals.h"
#include "interface_globals.h"
#include <iostream>

void ScrollEngine::update(std::unique_ptr<GameObject> &object)
{

}


void ScrollEngine::move_world()
{
    if (engine_interface.move_world_enabled)
    {
        bool scroll_direction[4] = {false, false, false, false};
        for (auto& object : graphics_engine.render_buffer)
        {
 
            if (input_engine.arrow_keys.right)
            {
                scroll_direction[0] = true;
                object->set_position(object->physics.position.x + move_speed,object->physics.position.y);
			    sprite_engine.update(object);
            } else if (input_engine.arrow_keys.left)
            {
                scroll_direction[1] = true;
                object->set_position(object->physics.position.x - move_speed,object->physics.position.y);
			    sprite_engine.update(object);
            }
            if (input_engine.arrow_keys.up)
            {
                scroll_direction[2] = true;

                object->set_position(object->physics.position.x,object->physics.position.y-move_speed);
			    sprite_engine.update(object);                

            } else if (input_engine.arrow_keys.down)
            {
                scroll_direction[3] = true;
                object->set_position(object->physics.position.x,object->physics.position.y+move_speed);
			    sprite_engine.update(object);  

            }
        }
        if (scroll_direction[0])
        {
            accumulated_x += move_speed;
        }
        if (scroll_direction[1])
        {
            accumulated_x -= move_speed;
        }
        if (scroll_direction[2])
        {
            accumulated_y -= move_speed;
        }
        if (scroll_direction[3])
        {
            accumulated_y += move_speed;
        }

        if (engine_interface.set_to_zero)
        {
            for (auto& object : graphics_engine.render_buffer)
            {
                object->set_position(object->physics.position.x - accumulated_x, object->physics.position.y - accumulated_y);
			    sprite_engine.update(object);  


            }
            accumulated_x = 0;
            accumulated_y = 0;
            engine_interface.set_to_zero = false;


        }


    }
}
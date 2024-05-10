#include "scroll_engine.h"
#include "engine_globals.h"
#include "interface_globals.h"
#include <iostream>


ScrollEngine::ScrollEngine()
{
    left_x_scroll_threshold = graphics_engine.width/2;
    right_x_scroll_threshold = graphics_engine.width/4;
    up_y_scroll_threshold = graphics_engine.width/4;
    down_y_scroll_threshold = graphics_engine.width/2;
}
void ScrollEngine::update(GameObject* object)
{
    if (scroll_x_position)
    {
        if (!object->camera.camera_active)
        {
            object->physics.position.x = (object->physics.position.x - scroll_x_velocity*dt - 0.5*(object->physics.force.x/object->physics.mass)*pow(dt,2));
        } 
    }

    if (scroll_y_position)
    {
        if (!object->camera.camera_active)
        {
            object->physics.position.y = (object->physics.position.y - scroll_y_velocity*dt );
        }
    }
    

}


void ScrollEngine::move_world()
{
    if (engine_interface.move_world_enabled)
    {
        bool scroll_direction[4] = {false, false, false, false};
        for (auto& object_locator : graphics_engine.render_buffer)
        {
            GameObject* object = object_locator.item;
 
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
            for (auto& object_locator : graphics_engine.render_buffer)
            {   GameObject* object = object_locator.item;
                object->set_position(object->physics.position.x - accumulated_x, object->physics.position.y - accumulated_y);
			    sprite_engine.update(object);  


            }
            accumulated_x = 0;
            accumulated_y = 0;
            engine_interface.set_to_zero = false;
        }
    }
}
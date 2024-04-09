#include "camera_engine.h"
#include "engine_globals.h"
#include <iostream>



CameraEngine::CameraEngine()
{
    capture_x_velocity = false;
}
void CameraEngine::update(std::unique_ptr<GameObject> &object)
{
    if (object->camera.camera_active)
    {

        // detect direction change
        if (input_engine.arrow_keys.left && current_direction.right || input_engine.arrow_keys.right && current_direction.left)
        {
            object->physics.freeze_x_position = false;
            scroll_engine.scroll_x_position = false;
            capture_x_velocity = false;
        }
        // logic for scrolling scene to left while object moves to right
        if (object->physics.position.x >= scroll_engine.left_x_scroll_threshold && !input_engine.arrow_keys.left && input_engine.arrow_keys.right)
        {
            current_direction.right = true;
            current_direction.left = false;

            object->physics.freeze_x_position = true;
            if (!capture_x_velocity)
            {
                scroll_engine.scroll_x_position = true;
                x_velocity_capture = object->physics.velocity.x;
                capture_x_velocity = true;
            }

            if (scroll_engine.scroll_x_position)
            {
                if (input_engine.arrow_keys.right)
                {
                    scroll_engine.scroll_x_velocity = x_velocity_capture;
                } else {
                    scroll_engine.scroll_x_velocity = 0;
                }
            }
        } else if (object->physics.position.x <= scroll_engine.right_x_scroll_threshold && !input_engine.arrow_keys.right && input_engine.arrow_keys.left)
        {
            current_direction.left = true;
            current_direction.right = false;
            object->physics.freeze_x_position = true;

            if (!capture_x_velocity)
            {
                scroll_engine.scroll_x_position = true;
                x_velocity_capture = object->physics.velocity.x;
                capture_x_velocity = true;
            }


            if (scroll_engine.scroll_x_position)
            {
                if (input_engine.arrow_keys.left)
                {
                    scroll_engine.scroll_x_velocity = x_velocity_capture;
                } else {
                    scroll_engine.scroll_x_velocity = 0;
                }
            }

        
        } else{
            object->physics.freeze_x_position = false;
            scroll_engine.scroll_x_position = false;
            capture_x_velocity = false;
        }



    }
}

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
     
        if ( (object->physics.position.x >= scroll_engine.left_x_scroll_threshold && object->physics.velocity.x > 0) ||
             (object->physics.position.x <= scroll_engine.right_x_scroll_threshold && object->physics.velocity.x < 0)) 
        {  
            object->physics.freeze_x_position = true;
            scroll_engine.scroll_x_position = true;
            scroll_engine.scroll_x_velocity = object->physics.velocity.x;
        } else{
            object->physics.freeze_x_position = false;
            scroll_engine.scroll_x_position = false;
            scroll_engine.scroll_x_velocity = object->physics.velocity.x;

        }

    }
}

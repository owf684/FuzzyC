#include "engine_globals.h"
#include <iostream>



CameraEngine::CameraEngine()
{
}

/* Function: update
*
*   Purpose: This function calls other functions
*/
void CameraEngine::update(GameObject* object)
{
    handle_camera(object);
}

/* Function: handle_camera
*
* Purpose: This function checks the object position of an object assigned with the active camera
* and decides whether to enable scrolling in the x or y axis. The thresholds are controlled by two sliders
* in the UI. 
*/
void CameraEngine::handle_camera(GameObject* object)
{

    if (object->camera.camera_active)
    {
     
        if ( (object->physics.position.x >= scroll_engine.left_x_scroll_threshold && object->physics.velocity.x > 0) ||
             (object->physics.position.x <= scroll_engine.right_x_scroll_threshold && object->physics.velocity.x < 0)) 
        {  
            object->physics.freeze_x_position = true;
            scroll_engine.scroll_x_position = true;
            scroll_engine.scroll_x_velocity = object->physics.velocity.x;
            
            scroll_engine.accumulated_x -= scroll_engine.scroll_x_velocity*dt; - 0.5*(object->physics.force.x/object->physics.mass)*pow(dt,2);

        } else{
            object->physics.freeze_x_position = false;
            scroll_engine.scroll_x_position = false;
            scroll_engine.scroll_x_velocity = 0;

        }
       
        if ( (object->physics.position.y >= scroll_engine.down_y_scroll_threshold && object->physics.velocity.y > 0) ||
             (object->physics.position.y <= scroll_engine.up_y_scroll_threshold && object->physics.velocity.y < 0)) 
        {  
            object->physics.freeze_y_position = true;
            scroll_engine.scroll_y_position = true;
            scroll_engine.scroll_y_velocity = object->physics.velocity.y;
            
            scroll_engine.accumulated_y -= scroll_engine.scroll_y_velocity*dt; - 0.5*(object->physics.force.y/object->physics.mass)*pow(dt,2);


        } else{
            object->physics.freeze_y_position = false;
            scroll_engine.scroll_y_position = false;
            scroll_engine.scroll_y_velocity = 0;

        }

    }
}


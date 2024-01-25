/* Name of Program: collision_engine
*
* Purpose: this detects collisions
* between all the objects in the render
* buffer
*
* Version: v0.1.0
*
* Author: Christopher Corona
*
* Assumptions: None
*
* Weakness: Current implementation
* is very inefficient. However I'm
* not at the stage of development 
* where I can optimize the collision
* algorithm
*
* Things to do: Need to implement 
* left, right, and up collision
* detection 
*
*/

#include "collision_engine.h"


/* Function: update()
*
* Purpose: This updates the objects collider
* by calling all the collision_detection functions
*
* Input Limits: 
* all arguments must be unique_ptrs to derived game_objects
*/

InputEngine input_ec;

void CollisionEngine::update(std::unique_ptr<GameObject>& object, 
                             std::vector< std::unique_ptr<GameObject> >& render_buffer,
                             InputEngine& input_engine) 
{
    // update inputs
    input_ec = input_engine;

    // reset colliders
    object->collider.reset();

    // update collider position
    object->collider.box.x = object->physics.position.x;
    object->collider.box.y = object->physics.position.y;

    //update collider dimensions
    object->collider.box.w = object->sprite.rect.w;
    object->collider.box.h = object->sprite.rect.h;

    int i  = 0;

    for(auto& other : render_buffer)
    {
        left_collision(object, other);
        right_collision(object,other);        
        down_collision(object, other);
        up_collision(object, other);
        
        ++i;
    }

    handle_physics(object);
}

/* Function: down_collision()
*
*  Purpose: detects downward collision through
*  a series of coordinate checks
*
*/

bool CollisionEngine::down_collision(std::unique_ptr<GameObject>& current_object, std::unique_ptr<GameObject>& other)
{
    auto c_coll  = current_object->collider;
    auto o_coll = other->collider;

    
    if ( (c_coll.bottom() > o_coll.top() && c_coll.top() < o_coll.top() )  && // check y 
        (
        (c_coll.right() > o_coll.left()    &&  c_coll.right() < o_coll.right())   ||
        (c_coll.center_x() > o_coll.left() && c_coll.center_x() < o_coll.right()) || 
        (c_coll.left() > o_coll.left() && c_coll.left() < o_coll.right()) 
        ) 
         
    ) 
    {
        current_object->collider.is.down = true;
        if (!current_object->physics.pause) current_object->set_position( current_object->physics.position.x , other->physics.position.y - current_object->sprite.current->h+1);

    }
}

/* Function: up_collision()
*
*  Purpose: detects upward collision through
*  a series of coordinate checks
*
*/

bool CollisionEngine::up_collision(std::unique_ptr<GameObject>& current_object, std::unique_ptr<GameObject>& other)
{
    auto c_coll  = current_object->collider;
    auto o_coll = other->collider;

    if (c_coll.top() < o_coll.bottom() && 
        c_coll.bottom() > o_coll.bottom())
    {
        if (c_coll.center_x() > o_coll.left() && c_coll.center_x() < o_coll.right() ||
            c_coll.left() > o_coll.left() && c_coll.left() < o_coll.right() ||
            c_coll.right() > o_coll.left() && c_coll.right() < o_coll.right() )
        {
            current_object->collider.is.up = true;
        }
    }
}

/* Function: left_collision()
*
*  Purpose: detects leftward collision through
*  a series of coordinate checks
*
*/

bool CollisionEngine::left_collision(std::unique_ptr<GameObject>& current_object, std::unique_ptr<GameObject>& other)
{       
    auto c_coll  = current_object->collider;
    auto o_coll = other->collider;

    if (c_coll.left() <= o_coll.right() && 
        c_coll.right() > o_coll.left() &&
        c_coll.right() > o_coll.right() &&
        !(c_coll.top() > o_coll.bottom() && c_coll.bottom() > o_coll.bottom() ) &&
        !(c_coll.bottom() > o_coll.top() && c_coll.top() > o_coll.top() ) )
    {
        if (c_coll.center_y() > o_coll.top() && c_coll.center_y() < o_coll.bottom() ||
            c_coll.top() > o_coll.top() && c_coll.top() < o_coll.bottom() ||
            c_coll.bottom()-2 > o_coll.top() && c_coll.bottom() < o_coll.bottom()-2)
        {
                
        current_object->collider.is.left = true;
       if (!current_object->physics.pause) current_object->set_position(o_coll.right(),c_coll.top());
        }
    }

}

/* Function: right_collision()
*
*  Purpose: detects rightward collision through
*  a series of coordinate checks
*
*/

bool CollisionEngine::right_collision(std::unique_ptr<GameObject>& current_object, std::unique_ptr<GameObject>& other)
{
    auto c_coll  = current_object->collider;
    auto o_coll = other->collider;

    if (c_coll.right() >= o_coll.left() && 
        c_coll.right() < o_coll.right() && 
        c_coll.left() < o_coll.left() &&
        !( c_coll.top() > o_coll.bottom() && c_coll.bottom() > o_coll.bottom() ))
    {
        if (c_coll.center_y() > o_coll.top() && c_coll.center_y() < o_coll.bottom() ||
            c_coll.top() > o_coll.top() && c_coll.top() < o_coll.bottom() ||
            c_coll.bottom() > o_coll.top() && c_coll.bottom() < o_coll.bottom() )
        {

        current_object->collider.is.right = true;
        if (!current_object->physics.pause) current_object->set_position(o_coll.left()-c_coll.box.w, c_coll.top());
        }
    }

}

/* Function: handle_physics()
*
* Purpose: This function updates
* the physics velocities and accelerations
* of the objects based on the collisions
* detected
*
*/

void CollisionEngine::handle_physics(std::unique_ptr<GameObject>& current_object)
{
    if ( (input_ec.arrow_keys.left && current_object->collider.is.left) ||
         (input_ec.arrow_keys.right && current_object->collider.is.right))
    {
        current_object->physics.velocity.x = 0;
        current_object->physics.acceleration.x = 0;
    }

    if (!input_ec.arrow_keys.up && current_object->collider.is.down)
    {
        current_object->physics.velocity.y = 0;
        current_object->physics.acceleration.y = 0;
    }

    if (current_object->collider.is.up)
    {
        current_object->physics.velocity.y *= -.5;
        current_object->physics.acceleration.y *= -.5;
    }

}
    

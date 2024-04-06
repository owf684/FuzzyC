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
* Things to do: 
* Need to implement system where users can 
* define what type of collisions an object
* delivers to other objects
*/

#include "collision_engine.h"
#include "engine_globals.h"


/* Function: update()
*
* Purpose: This updates the objects collider
* by calling all the collision_detection functions
*
* Input Limits: 
* all arguments must be unique_ptrs to derived game_objects
*/



void CollisionEngine::update(std::unique_ptr<GameObject>& object) 
{
    // reset colliders
    object->collider.reset();

    // update collider position
    object->collider.box.x = object->physics.position.x;
    object->collider.box.y = object->physics.position.y;

    //update collider dimensions
    object->collider.box.w = object->sprite.rect.w;
    object->collider.box.h = object->sprite.rect.h;

    int i  = 0;

    for(auto& other : graphics_engine.render_buffer)
    {
        left_collision(object, other);
        right_collision(object,other);        
        down_collision(object, other);
        up_collision(object, other);
        
        ++i;
    }
}

/* Function: down_collision()
*
*  Purpose: detects downward collision through
*  a series of coordinate checks
*
*/

 void CollisionEngine::down_collision(std::unique_ptr<GameObject>& current_object, std::unique_ptr<GameObject>& other)
{
    if (above(current_object, other))
    {
        current_object->collider.is.down = true;

        if(!current_object->physics.pause)
        {    
            // calculate overlap and correct y position

            float overlap = current_object->collider.bottom() - other->collider.top();
            float corrected_y_position = current_object->physics.position.y - overlap;
            current_object->set_position(current_object->physics.position.x, corrected_y_position);
        }

        y_inelastic_collision(current_object,other);

    }
}

/* Function: up_collision()
*
*  Purpose: detects upward collision through
*  a series of coordinate checks
*
*/

void CollisionEngine::up_collision(std::unique_ptr<GameObject>& current_object, std::unique_ptr<GameObject>& other)
{
    if ( below(current_object,other) )
    {
        if (!current_object->physics.pause)
        {
            // calculate overlap and correct y position
            
            float overlap = current_object->collider.top() - other->collider.bottom();
            float corrected_y_position = current_object->physics.position.y - overlap;
            current_object->set_position(current_object->physics.position.x, corrected_y_position);

        }

        y_elastic_collision(current_object,other);
    }

}

/* Function: left_collision()
*
*  Purpose: detects leftward collision through
*  a series of coordinate checks
*
*/

void CollisionEngine::left_collision(std::unique_ptr<GameObject>& current_object, std::unique_ptr<GameObject>& other)
{       
    if (to_right(current_object,other))
    {

        if (!current_object->physics.pause)
        {
            // calculate overlap and correct x position
            float overlap = current_object->collider.left()-other->collider.right();
            float corrected_x_position = current_object->physics.position.x - overlap;
            current_object->set_position(corrected_x_position,current_object->physics.position.y);
        }

        current_object->collider.is.left = true;
        x_inelastic_collision(current_object,other);
        
    }

}

/* Function: right_collision()
*
*  Purpose: detects rightward collision through
*  a series of coordinate checks
*
*/

void CollisionEngine::right_collision(std::unique_ptr<GameObject>& current_object, std::unique_ptr<GameObject>& other)
{
    if ( to_left(current_object,other) )
    {

        current_object->collider.is.right = true;
        
        if (!current_object->physics.pause ) 
        {
            // calculate overlap and correct x position
            float overlap = current_object->collider.right() - other->collider.left();
            float corrected_x_position = current_object->physics.position.x - overlap;
            current_object->set_position(corrected_x_position,current_object->physics.position.y);
       
        }

        x_inelastic_collision(current_object,other);

        
    }

}


/* Funcion: above()
*
* Purpose: This function returns true
* if object_1 is above object 2 and 
* is overlapping it
*
*/

bool CollisionEngine::above(std::unique_ptr<GameObject>& object_1, std::unique_ptr<GameObject>& object_2)
{
    int x_tolerance = 0;

    // check the y axis

    if (object_1->collider.bottom() > object_2->collider.top() &&
        object_1->collider.top() < object_2->collider.top())
    {
        // check the x axis
    
        if (object_1->collider.center_x() > object_2->collider.left()+x_tolerance &&
            object_1->collider.center_x() < object_2->collider.right()-x_tolerance)
            return true;
        else if (object_1->collider.left() > object_2->collider.left()+x_tolerance &&
                 object_1->collider.left() < object_2->collider.right()-x_tolerance)
            return true;
        else if (object_1->collider.right() > object_2->collider.left()+x_tolerance &&
                 object_1->collider.right() < object_2->collider.right()-x_tolerance)
            return true;
        else 
            return false;
    } else return false;
}

/* Function: below()
*
* Purpose: this function returns true
* if object_1 is below object_2 and 
* is overlapping it
*
*/

bool CollisionEngine::below(std::unique_ptr<GameObject>& object_1, std::unique_ptr<GameObject>& object_2)
{
    int x_tolerance = 0;
    // check the y xais
    
    if ( object_1->collider.top() < object_2->collider.bottom() &&
         object_1->collider.top() > object_2->collider.top() &&
         object_1->collider.bottom() > object_2->collider.bottom())
    {

        // check the x axis
      
        if (object_1->collider.left() > object_2->collider.left()+x_tolerance &&
            object_1->collider.left() < object_2->collider.right()-x_tolerance)
        {
            return true;

        } else if (object_1->collider.right() > object_2->collider.left()+x_tolerance &&
                   object_1->collider.right() < object_2->collider.right()-x_tolerance)
        {
            return true;

        } else if (object_1->collider.center_x() > object_2->collider.left()+x_tolerance &&
                   object_1->collider.center_x() < object_2-> collider.right()-x_tolerance)
        {
            return true;

        } else return false;


    } else return false;
}

/* Function: to_left()
*
* Purpose: This function returns true
* when object 1 is to left of object 2
* and is overlapping it
*
*/
bool CollisionEngine::to_left(std::unique_ptr<GameObject>& object_1, std::unique_ptr<GameObject>& object_2)
{
    // this tolerance prevents objects from falsely triggering right collisions when bottom
    // sinks underneath a surface

    int y_tolerance = 10;

    // check x axis
    if (object_1->collider.right() > object_2->collider.left() &&
        object_1->collider.left() < object_2->collider.left() &&
        object_1->collider.right() < object_2->collider.right() &&
        object_1->collider.left() < object_2->collider.right() &&
        object_1->collider.center_x() < object_2->collider.right() &&
        object_1->collider.center_x() < object_2->collider.left() )
        
    {


        // check y axis
        if (object_1->collider.center_y() > object_2->collider.top() && 
            object_1->collider.center_y() < object_2->collider.bottom())

            return true;

        else if ( object_1->collider.top() > object_2->collider.top() &&
                  object_1->collider.top() + 2*y_tolerance < object_2->collider.bottom())

            return true;

        else if ( object_1->collider.bottom()-y_tolerance > object_2->collider.top() &&
                  object_1->collider.bottom()-y_tolerance < object_2->collider.bottom())

            return true;

        else return false;


    } else return false;

}

/* Function: to_right()
*
* Purpose: this function returns true
* when object_1 is to the right of object_2
* and is overlapping it
*/

bool CollisionEngine::to_right(std::unique_ptr<GameObject>& object_1, std::unique_ptr<GameObject>& object_2)
{
    // this tolerance prevents objects from falsely triggering right collisions when bottom
    // sinks underneath a surface
    int y_tolerance = 10;
    
    // check x axis

    if (object_1->collider.left()  < object_2->collider.right() &&
        object_1->collider.right() > object_2->collider.right() &&
        object_1->collider.left() > object_2->collider.left() &&
        object_1->collider.right() > object_2->collider.left() &&
        object_1->collider.center_x() > object_2->collider.right() &&
        object_1->collider.center_x() > object_2->collider.left())
    {

        // check y axis
        if (object_1->collider.center_y() > object_2->collider.top() && 
            object_1->collider.center_y() < object_2->collider.bottom())

            return true;

        else if ( object_1->collider.top() > object_2->collider.top() &&
                  object_1->collider.top()+ 2*y_tolerance < object_2->collider.bottom())

            return true;

        else if ( object_1->collider.bottom()-y_tolerance > object_2->collider.top() &&
                  object_1->collider.bottom()-y_tolerance < object_2->collider.bottom())

            return true;

        else return false;


    } else return false;
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
    

    if (current_object->collider.is.up)
    {
        current_object->physics.velocity.y *= -.5;
        current_object->physics.acceleration.y *= -.5;
    }

}

/* Function: x_inelastic_collision()
*
* Purpose: This function calculates the 
* inelastic collision between current_object
* and other in the x_axis
*
*/  

void CollisionEngine::x_inelastic_collision(std::unique_ptr<GameObject>& current_object, std::unique_ptr<GameObject>& other)
{
    // inelastic collisions
    // V = (mass_a * velocity_a - mass_b * velocity_b) / (mass_a + mass_b)

    float p = current_object->physics.momentum_x() - other->physics.momentum_x();
    float m = current_object->physics.mass + other->physics.mass;
    float v = p/m;


    current_object->physics.velocity.x = v;
    other->physics.velocity.x = v;

}

/* Function: y_inelastic_collision()
*
* Purpose: This function calculates the 
* inelastic collision between current_object
* and other in the y_axis
*
*/  

void CollisionEngine::y_inelastic_collision(std::unique_ptr<GameObject>& current_object, std::unique_ptr<GameObject>& other)
{
    // inelastic collisions
    // V = (mass_a * velocity_a - mass_b * velocity_b) / (mass_a + mass_b)

    float p = current_object->physics.momentum_y() - other->physics.momentum_y();
    float m = current_object->physics.mass + other->physics.mass;
    float v = p/m;

    current_object->physics.velocity.y = v;
    other->physics.velocity.y = v;

}

/* Function: y_elastic_collision()
*
* Purpose: this function calculates the 
* elastic collision between current_object 
* and other in the y_axis
*
*/

void CollisionEngine::y_elastic_collision(std::unique_ptr<GameObject>& current_object, std::unique_ptr<GameObject>& other)
{
    current_object->physics.impulse.y = 0;
/*
    v1 = ((m1 – m2)*u1 + 2*m2*u2) / (m1 + m2)
    v2 = ((m2 – m1)*u2 + 2*m1*u1) / (m1 + m2)
*/
    // calculate total mass
    int total_mass = current_object->physics.mass + other->physics.mass;

    // working out v1 terms t
    float v1_t1 = (current_object->physics.mass - other->physics.mass)*current_object->physics.velocity.y;
    float v1_t2 = 2*other->physics.mass*other->physics.velocity.y;

    // working out v2 terms t
    float v2_t1 = (other->physics.mass - current_object->physics.mass)*other->physics.velocity.y;
    float v2_t2 = 2*current_object->physics.mass*current_object->physics.velocity.y;

    // calculate v1 velocity
    float v1 = (v1_t1 + v1_t2) / total_mass;

    // calculate v2 velocity 
    float v2 = (v2_t1 + v2_t2) / total_mass;


    // update object velocities
    current_object->physics.velocity.y = v1;

    other->physics.velocity.y = v2;
    

}

/* Function: x_elastic_collision()
*
* Purpose: this function calculates the 
* elastic collision between current_object 
* and other in the x_axis
*
*/

void CollisionEngine::x_elastic_collision(std::unique_ptr<GameObject>& current_object,std::unique_ptr<GameObject>& other)
{
    /*
    v1 = ((m1 – m2)*u1 + 2*m2*u2) / (m1 + m2)
    v2 = ((m2 – m1)*u2 + 2*m1*u1) / (m1 + m2)
*/
    // calculate total mass
    int total_mass = current_object->physics.mass + other->physics.mass;

    // working out v1 terms t
    float v1_t1 = (current_object->physics.mass - other->physics.mass)*current_object->physics.velocity.x;
    float v1_t2 = 2*other->physics.mass*other->physics.velocity.x;

    // working out v2 terms t
    float v2_t1 = (other->physics.mass - current_object->physics.mass)*other->physics.velocity.x;
    float v2_t2 = 2*current_object->physics.mass*current_object->physics.velocity.x;

    // calculate v1 velocity
    float v1 = (v1_t1 + v1_t2) / total_mass;

    // calculate v2 velocity 
    float v2 = (v2_t1 + v2_t2) / total_mass;


    // update object velocities
    current_object->physics.velocity.x = v1;

    other->physics.velocity.x = v2;

}

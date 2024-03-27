/* Name of Program: game_object
*
* Purpose: This is the base class
* game object that contains all 
* the necessary object components
* needed for physics, sprites, etc.
* This object by itself is not intended
* for use in creating actual game_objects
* It's purpose is purely inheritance &
* polymorphism
*
* Author: Christopher Corona
*
* Version: v0.1.0
*
*/

#include "game_object.h"
#include "iostream"
using namespace std;



/* Function: update
*
* Purpose: place holder.
* This function is overriden
* by the derived classes
*
*/

void GameObject::update()
{
}

/* Function: set_position()
*
* Purpose: This function updates both
* the physics and sprites position in
* one call.
*
*/

void GameObject::set_position(int x, int y)
{
    // update physics
    physics.position.x = x; physics.position.y = y;

    // update sprite
    sprite.position.x = x; sprite.position.y = y;

    // update collider
    collider.box.x = x; collider.box.y = y;
}


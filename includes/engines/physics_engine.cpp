/* Name of Program: physics_engine
*
* Purpose: This updates the objects
* physics component
*
* Author: Christopher Corona
*
* Version: v0.1.0
*
*/

#include "physics_engine.h"
#include "engine_globals.h"



/* Name of function: update()
*
* Purpose: This function updates the objects
* physics components
*
* TODO: figure out a better way to handle down collision
*
*/

void PhysicsEngine::update(GameObject* object)
{


    if (!object->physics.pause)  object->physics.update(dt);

  

}
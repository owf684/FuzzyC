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



/* Name of function: update()
*
* Purpose: This function updates the objects
* physics components
*
* TODO: figure out a better way to handle down collision
*
*/

void PhysicsEngine::update(std::unique_ptr<GameObject>& object,InputEngine& input_engine, float dt)
{


    if (!object->physics.pause)  object->physics.update(980.0,dt);

  

}
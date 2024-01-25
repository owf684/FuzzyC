/* Name of program: sprite_engine
*
* Purpose: This update the sprite component of 
* all game_objects position.
*
* Author: Christopher Corona
*
* Version : v0.1.0
*
*/

#include "sprite_engine.h"



/* Name of function: update()
*
* Purpose: This updates the objects
* sprite position
* using the objects physics position
*
*/

void SpriteEngine::update(std::unique_ptr<GameObject> &object)
{
    object->sprite.set_position(object->physics.position.x,object->physics.position.y);
}

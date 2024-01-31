#ifndef MAIN_H
#define MAIN_H

#include "./includes/engines/graphics_engine.h"
#include "./includes/engines/input_engine.h"
#include "./includes/engines/sprite_engine.h"
#include "./includes/engines/physics_engine.h"
#include "./includes/engines/collision_engine.h"
#include "./includes/objects/game_object.h"
#include "./game_data/objects/player_object/bird.h"
#include "./game_data/objects/environment_objects/test_platform.h"

#include <ctime>
#include <unistd.h>
#include <iostream>
#include <chrono>
#include <thread>
#include <cmath>
#include <SDL2/SDL.h>
#include <memory>




/* Frame Rate Variables
*
*
*/
float dt_f = 0;
const float frames_per_second_f = 60.0;
const float micro_seconds_f = pow(10,6); // == 1 / micro_seconds
const float frame_duration_f = (1.0 / frames_per_second_f)*micro_seconds_f;
float time_elapsed_f = 0.0;


/* Engines Variables
*
* Name Description: The engines' name indicates
* what component the engine will update.
* the name is followed by '_e' to indicate
* that these variables are engine types
*/
GraphicsEngine graphics_e(800,600,32);
InputEngine input_e;
SpriteEngine sprite_e;
PhysicsEngine physics_e;
CollisionEngine collision_e;

/* GameObject Testing
*
*
*/

std::unique_ptr<Bird> bird_ptr( new Bird() );
std::unique_ptr<TestPlatform> platform_ptr ( new TestPlatform() );
std::unique_ptr<TestPlatform> platform_ptr_2 ( new TestPlatform() );
std::unique_ptr<TestPlatform> platform_ptr_3 ( new TestPlatform() );
std::unique_ptr<TestPlatform> platform_ptr_4 ( new TestPlatform() );
std::unique_ptr<TestPlatform> platform_ptr_5 ( new TestPlatform() );



#endif 

#ifndef ENGINE_GLOBALS_H
#define ENGINE_GLOBALS_H

#include "./engines/engine_interface.h"
#include "./engines/graphics_engine.h"
#include "./engines/input_engine.h"
#include "./engines/sprite_engine.h"
#include "./engines/physics_engine.h"
#include "./engines/collision_engine.h"
#include "./objects/game_object.h"
#include "./objects/object_handler.h"

extern EngineInterface engine_interface;
extern GraphicsEngine graphics_engine;
extern InputEngine input_engine;
extern SpriteEngine sprite_engine;
extern PhysicsEngine physics_engine;
extern CollisionEngine collision_engine;

extern float dt;
extern float frames_per_second_f;
extern const float micro_seconds_f; 
extern const float frame_duration_f;
extern float time_elapsed_f;

extern ObjectHandler object_handler;

#endif

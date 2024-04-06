#ifndef ENGINE_GLOBALS_H
#define ENGINE_GLOBALS_H

#include "./engines/engine_interface.h"
#include "./engines/graphics_engine.h"
#include "./engines/input_engine.h"
#include "./engines/sprite_engine.h"
#include "./engines/physics_engine.h"
#include "./engines/collision_engine.h"
#include "./objects/game_object.h"
#include "./objects/rdoh.h"
#include "./objects/rdoh_util.h"
#include <map>
#include <any>

// engine globals
extern EngineInterface engine_interface;
extern GraphicsEngine graphics_engine;
extern InputEngine input_engine;
extern SpriteEngine sprite_engine;
extern PhysicsEngine physics_engine;
extern CollisionEngine collision_engine;

// frame rate globals
extern float dt;
extern float frames_per_second_f;
extern const float micro_seconds_f; 
extern const float frame_duration_f;
extern float time_elapsed_f;
extern std::map<std::string, std::any> objects_library;

// object globals
extern RDOH object_handler;
extern RdohUtil object_util;

#endif

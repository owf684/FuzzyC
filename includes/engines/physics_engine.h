#ifndef PHYSICS_ENGINE_H
#define PHYSICS_ENGINE_H

#include "../objects/game_object.h"
#include "../engines/input_engine.h"
#include <memory>


class PhysicsEngine
{
  public:
    void update(std::unique_ptr<GameObject>& object, InputEngine& input_engine, float dt);
    
};


#endif 

#pragma once
#ifndef PHYSICS_ENGINE_H
#define PHYSICS_ENGINE_H

#include <memory>
#include "game_object.h"

class PhysicsEngine
{
  public:
    void update(GameObject* object);
    
};


#endif 

#pragma once
#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include "../components/sprite_component.h"
#include "../components/physics_component.h"
#include "../components/collider_component.h"
#include "../components/camera_component.h"
#include <memory>

class GameObject{
  public:
     
    Sprite sprite;
 
    PhysicsComponent physics;

    ColliderComponent collider;

    CameraComponent camera;

    std::string object_name;

    void set_position(float x, float y);
    
    virtual void update();
  
    virtual ~GameObject() = default;
  
};


#endif

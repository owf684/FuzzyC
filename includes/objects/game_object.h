#pragma once
#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include "sprite_component.h"
#include "physics_component.h"
#include "collider_component.h"
#include "camera_component.h"
#include <memory>

class GameObject{
  public:
    GameObject() 
    {
    }
    Sprite sprite;
 
    PhysicsComponent physics;

    ColliderComponent collider;

    CameraComponent camera;

    std::string object_name;

    void set_position(float x, float y);
    
    virtual void update();
  
    virtual ~GameObject() = default;

    virtual float getX() 
    {
      return physics.position.x;
    }

    virtual float getY() 
    {
      return physics.position.y;
    }

    virtual float getWidth()
    {
      return sprite.rect.w;
    }

    virtual float getHeight()
    {
      return sprite.rect.h;
    }
  
};


#endif

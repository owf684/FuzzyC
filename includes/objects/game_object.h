#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include "../components/sprite_component.h"
#include "../components/physics_component.h"
#include "../components/collider_component.h"
#include "../engines/input_engine.h"
#include <memory>

class GameObject{
  public:
     
    Sprite sprite;
 
    PhysicsComponent physics;

    ColliderComponent collider;

    int object_id;

    void set_position(int x, int y);
    
    virtual void update(InputEngine& input_engine);

    virtual ~GameObject() = default;
};


#endif

#ifndef SPRITE_ENGINE_H
#define SPRITE_ENGINE_H
#include "../objects/game_object.h"
#include <memory>





class SpriteEngine{
  
  public:
   void update(std::unique_ptr<GameObject> &object);

};



#endif

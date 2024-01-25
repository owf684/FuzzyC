#ifndef COLLISION_ENGINE_H
#define COLLISION_ENGINE_H

#include "../objects/game_object.h"
#include "../engines/input_engine.h"
#include <SDL/SDL.h>
#include <iostream>
#include <vector>
#include <memory>

class CollisionEngine{

    public:
    void  update(std::unique_ptr<GameObject>& object, 
    std::vector<std::unique_ptr<GameObject> >& render_buffer,
    InputEngine& input_engine);


    private:
        bool down_collision(std::unique_ptr<GameObject>& current_object,std::unique_ptr<GameObject>& other);
        bool up_collision(std::unique_ptr<GameObject>& current_object, std::unique_ptr<GameObject>& other);
        bool left_collision(std::unique_ptr<GameObject>& current_object, std::unique_ptr<GameObject>& other);
        bool right_collision(std::unique_ptr<GameObject>& current_object, std::unique_ptr<GameObject>& other);

        void handle_physics(std::unique_ptr<GameObject>& current_object);

};

#endif
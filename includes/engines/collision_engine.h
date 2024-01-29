#ifndef COLLISION_ENGINE_H
#define COLLISION_ENGINE_H

#include "../objects/game_object.h"
#include "../engines/input_engine.h"
#include <SDL2/SDL.h>
#include <iostream>
#include <vector>
#include <memory>

class CollisionEngine{

    public:
    void  update(std::unique_ptr<GameObject>& object, 
    std::vector<std::unique_ptr<GameObject> >& render_buffer,
    InputEngine& input_engine);


    private:
        // collision handlers
        bool down_collision(std::unique_ptr<GameObject>& current_object,std::unique_ptr<GameObject>& other);
        bool up_collision(std::unique_ptr<GameObject>& current_object, std::unique_ptr<GameObject>& other);
        bool left_collision(std::unique_ptr<GameObject>& current_object, std::unique_ptr<GameObject>& other);
        bool right_collision(std::unique_ptr<GameObject>& current_object, std::unique_ptr<GameObject>& other);
        
        // collision detection
        bool above(std::unique_ptr<GameObject>& object_1, std::unique_ptr<GameObject>& object_2);
        bool below(std::unique_ptr<GameObject>& object_1, std::unique_ptr<GameObject>& object_2);
        bool to_left(std::unique_ptr<GameObject>& object_1, std::unique_ptr<GameObject>& object_2);
        bool to_right(std::unique_ptr<GameObject>& object_1, std::unique_ptr<GameObject>& object_2);

        // collision physics
        void handle_physics(std::unique_ptr<GameObject>& current_object);
        void x_inelastic_collision(std::unique_ptr<GameObject>& current_object,std::unique_ptr<GameObject>& other);
        void y_inelastic_collision(std::unique_ptr<GameObject>& current_object, std::unique_ptr<GameObject>& other);
        void y_elastic_collision(std::unique_ptr<GameObject>& current_object, std::unique_ptr<GameObject>& other);

};

#endif
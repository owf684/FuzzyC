#pragma once
#ifndef COLLISION_ENGINE_H
#define COLLISION_ENGINE_H

#include <iostream>
#include <vector>
#include <memory>
#include "game_object.h"

class CollisionEngine {

    public:
        void  update(GameObject* object);

        // collision handlers
        void down_collision(GameObject* current_object,GameObject* other);
        void up_collision(GameObject* current_object, GameObject* other);
        void left_collision(GameObject* current_object, GameObject* other);
        void right_collision(GameObject* current_object, GameObject* other);
        
        // collision detection
        bool above(GameObject* object_1, GameObject* object_2);
        bool below(GameObject* object_1, GameObject* object_2);
        bool to_left(GameObject* object_1, GameObject* object_2);
        bool to_right(GameObject* object_1, GameObject* object_2);

        // collision physics
        void handle_physics(GameObject* current_object);
        void x_inelastic_collision(GameObject* current_object,GameObject* other);
        void y_inelastic_collision(GameObject* current_object, GameObject* other);
        void x_elastic_collision(GameObject* current_object,GameObject* other);
        void y_elastic_collision(GameObject* current_object, GameObject* other);

};

#endif
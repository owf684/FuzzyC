#pragma once
#ifndef SCROLL_ENGINE_H
#define SCROLL_ENGINE_H

#include <memory>
#include "game_object.h"

class ScrollEngine {

    public:
        void update(std::unique_ptr<GameObject> &object);
        void move_world();
        int move_speed;
        int accumulated_y;
        int accumulated_x;
        bool scroll_x_position;
        float scroll_x_velocity;
        float left_x_scroll_threshold;
        float right_x_scroll_threshold;
        float last_x_position;
};


#endif

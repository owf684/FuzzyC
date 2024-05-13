#pragma once
#ifndef SCROLL_ENGINE_H
#define SCROLL_ENGINE_H

#include <memory>
#include "game_object.h"

class ScrollEngine {

    public:
        ScrollEngine();
        void update(GameObject* object);
        void move_world();
        int move_speed;
        float accumulated_y;
        float accumulated_x;
        bool scroll_x_position;
        float scroll_x_velocity;
        bool scroll_y_position;
        float scroll_y_velocity;
        int left_x_scroll_threshold;
        int right_x_scroll_threshold;
        int up_y_scroll_threshold;
        int down_y_scroll_threshold;        
        float last_x_position;
};


#endif

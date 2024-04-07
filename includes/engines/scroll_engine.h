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
};


#endif

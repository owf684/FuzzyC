#pragma once
#ifndef CAMERA_ENGINE_H
#define CAMERA_ENGINE_H
#include <memory>
#include "game_object.h"

class CameraEngine {
    public:
        CameraEngine();
        void update(std::unique_ptr<GameObject> &object);
        bool capture_x_velocity;
        float x_velocity_capture;
        struct direction
        {
            bool left;
            bool right;
        };
        direction current_direction;
};

#endif
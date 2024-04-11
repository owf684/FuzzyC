#pragma once
#ifndef CAMERA_ENGINE_H
#define CAMERA_ENGINE_H
#include <memory>
#include "game_object.h"

class CameraEngine {
    public:
        CameraEngine();
        void update(std::unique_ptr<GameObject> &object);
        void handle_camera(std::unique_ptr<GameObject> &object);
};

#endif
#pragma once
#ifndef CAMERA_ENGINE_H
#define CAMERA_ENGINE_H
#include <memory>
#include "game_object.h"

class CameraEngine {
    public:
        CameraEngine();
        void update(GameObject* object);
        void handle_camera(GameObject* object);
};

#endif
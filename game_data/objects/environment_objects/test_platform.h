#ifndef TEST_PLATFORM_H
#define TEST_PLATFORM_H

#include "../../../includes/objects/game_object.h"
#include "../../../includes/engines/input_engine.h"

class TestPlatform : public GameObject{

public:
    void update(InputEngine& input_engine) override;
    TestPlatform();
};

#endif
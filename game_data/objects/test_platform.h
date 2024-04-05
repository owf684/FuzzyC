#ifndef TEST_PLATFORM_H
#define TEST_PLATFORM_H

#include "engine_globals.h"

class TestPlatform : public GameObject{

public:
    void update() override;
    TestPlatform();
    std::unique_ptr<GameObject> generate_object() 
        {
            std::unique_ptr<TestPlatform> object(new TestPlatform);

            return  object;
        }
        
};

#endif
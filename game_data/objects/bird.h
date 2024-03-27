#ifndef BIRD_H
#define BIRD_H

#include "engine_globals.h"



class Bird : public GameObject 
{
    public:
        Bird();
        void update() override;

        void move_horizontal();
};

extern "C"
{
    std::unique_ptr<GameObject> generate_object()
    {
        std::unique_ptr<Bird> object(new Bird);

        return  object;
    }
}

#endif
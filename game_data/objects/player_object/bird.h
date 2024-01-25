#ifndef BIRD_H
#define BIRD_H


#include "../../../includes/objects/game_object.h"
#include "../../../includes/engines/input_engine.h"




class Bird : public GameObject 
{
    public:
        Bird();
        void update(InputEngine& input_engine) override;

        void move_horizontal(InputEngine& input_engine);
};


#endif
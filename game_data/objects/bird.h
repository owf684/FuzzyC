#ifndef BIRD_H
#define BIRD_H
#include "engine_globals.h"

class bird : public GameObject 
{
    public:
        bird();

        bool first_pass;
     
        void update() override;

        void move_horizontal();


};



#endif
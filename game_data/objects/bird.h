#ifndef BIRD_H
#define BIRD_H
#include "engine_globals.h"




class bird : public GameObject 
{
    public:
        bird();

        std::unique_ptr<bird> generate_object()
        {
            std::unique_ptr<bird> object(new bird);

            return  object;
        }
        
        void update() override;

        void move_horizontal();


};



#endif
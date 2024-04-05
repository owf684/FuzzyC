#include "bird.h"
#include "iostream"

using namespace std;

bird::bird()
{   // open a json file maybe and read bird attributes then set them accordingly

    try {
    sprite.set_current("./game_data/assets/bird.bmp");
    }
    catch(...){

        system("pwd");

    }
    physics.gravity = 980;
}


void bird::update()
{
    move_horizontal();    

}


void bird::move_horizontal()
{
    if (input_engine.arrow_keys.up &&  collider.is.down) // bug here for some reason this true upon engine start. screws things up
    {
        //move up
        physics.impulse.y = -10000;
    }
    if (input_engine.arrow_keys.right)
    {
        // move right
        physics.velocity.x = 250;
    }

    if (input_engine.arrow_keys.left)
    {
        // move left
        physics.velocity.x = -250;
    }


    if (!input_engine.arrow_keys.left && !input_engine.arrow_keys.right)
    {
        if (physics.velocity.x > 0)
        {
            physics.velocity.x -= 5;
        }

        if ( physics.velocity.x < 0)
        {
            physics.velocity.x += 5;
        }
    }
    
    if (input_engine.awsd.s)
    {
        // move down?
    }



}


#include "bird.h"
#include "iostream"
using namespace std;

Bird::Bird()
{   // open a json file maybe and read bird attributes then set them accordingly
    sprite.set_current("./assets/bird.bmp");
    object_id = 2;
    physics.gravity = 980;
}


void Bird::update(InputEngine& input_engine)
{
    move_horizontal(input_engine);    

}


void Bird::move_horizontal(InputEngine& input_engine)
{
    if (input_engine.arrow_keys.up &&  collider.is.down)
    {
        //move up
        physics.impulse.y = -7000;
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
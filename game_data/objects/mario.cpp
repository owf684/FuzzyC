#include "mario.h"
#include "iostream"
using namespace std;


mario::mario()
{
	sprite.set_current("./game_data/assets/mario_idle_right.bmp"); 
	physics.gravity = 980;
	collider.detect_collisions = true;
}


	void mario::update()
{


}
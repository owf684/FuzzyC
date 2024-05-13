#include "warp_pipe.h"
#include "iostream"
using namespace std;


warp_pipe::warp_pipe()
{
	sprite.set_current("./game_data/assets/warp_pipe.bmp"); 
	physics.gravity = 980;
	collider.detect_collisions = true;
}


	void warp_pipe::update()
{


}
#include "question_block.h"
#include "iostream"
using namespace std;


question_block::question_block()
{
	sprite.set_current("./game_data/assets/Question_block.bmp"); 
	physics.gravity = 980;
	collider.detect_collisions = true;
}

	void question_block::update()
{


}
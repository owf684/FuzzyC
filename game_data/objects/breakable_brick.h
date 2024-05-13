#ifndef BREAKABLE_BRICK_H 
#define BREAKABLE_BRICK_H
#include "engine_globals.h"


class  breakable_brick: public GameObject 
{ 
	public:
		breakable_brick();
		void update() override;

};
#endif

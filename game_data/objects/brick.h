#ifndef BRICK_H 
#define BRICK_H
#include "engine_globals.h"


class  brick: public GameObject 
{ 
	public:
		brick();
		void update() override;

};
#endif

#ifndef MARIO_H 
#define MARIO_H
#include "engine_globals.h"


class  mario: public GameObject 
{ 
	public:
		mario();
		void update() override;

};
#endif

#ifndef BREAKABLE_BRICK_H 
#define BREAKABLE_BRICK_H
#include "engine_globals.h"


class  breakable_brick: public GameObject 
{ 
	public:
		breakable_brick();

		std::unique_ptr<breakable_brick> generate_object() { 
			std::unique_ptr<breakable_brick> object( new breakable_brick);
			return  object;
		}


		void update() override;

};
#endif

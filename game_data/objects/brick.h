#ifndef BRICK_H 
#define BRICK_H
#include "engine_globals.h"


class  brick: public GameObject 
{ 
	public:
		brick();

		std::unique_ptr<brick> generate_object() { 
			std::unique_ptr<brick> object( new brick);
			return  object;
		}


		void update() override;

};
#endif

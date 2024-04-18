#ifndef MARIO_H 
#define MARIO_H
#include "engine_globals.h"


class  mario: public GameObject 
{ 
	public:
		mario();

		std::unique_ptr<mario> generate_object() { 
			std::unique_ptr<mario> object( new mario);
			return  object;
		}


		void update() override;

};
#endif

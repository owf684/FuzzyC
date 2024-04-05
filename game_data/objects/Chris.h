#ifndef CHRIS_H 
#define CHRIS_H
#include "engine_globals.h"


class  Chris: public GameObject 
{ 
	public:
		Chris();

		std::unique_ptr<Chris> generate_object() { 
			std::unique_ptr<Chris> object( new Chris);
			return  object;
		}


		void update() override;

};
#endif

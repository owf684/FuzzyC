#ifndef WARP_PIPE_H 
#define WARP_PIPE_H
#include "engine_globals.h"


class  warp_pipe: public GameObject 
{ 
	public:
		warp_pipe();

		std::unique_ptr<warp_pipe> generate_object() { 
			std::unique_ptr<warp_pipe> object( new warp_pipe);
			return  object;
		}


		void update() override;

};
#endif

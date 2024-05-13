#ifndef TEST_PLATFORM_H 
#define TEST_PLATFORM_H
#include "engine_globals.h"


class  test_platform: public GameObject 
{ 
	public:
		test_platform();
		void update() override;

};
#endif

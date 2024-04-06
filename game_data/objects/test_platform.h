#ifndef TEST_PLATFORM_H 
#define TEST_PLATFORM_H
#include "engine_globals.h"


class  test_platform: public GameObject 
{ 
	public:
		test_platform();

		std::unique_ptr<test_platform> generate_object() { 
			std::unique_ptr<test_platform> object( new test_platform);
			return  object;
		}


		void update() override;

};
#endif

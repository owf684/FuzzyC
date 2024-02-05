#include <iostream>
#include <cstring>
#include <sys/ipc.h>
#include <sys/shm.h>

class FuzzyEngineInterface {
    public:

        // Constructor 

        FuzzyEngineInterface();

        ~FuzzyEngineInterface();

        void read_memory();

        const char* sharedMemoryName;

        struct FEI{
            bool play;
        };

        FEI fuzzy_engine_interface;

};
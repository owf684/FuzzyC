#include "fuzzy_engine_interface.h"


FuzzyEngineInterface::FuzzyEngineInterface()
{
}

FuzzyEngineInterface::~FuzzyEngineInterface()
{  
    // destroy shared memory segment
    key_t key = ftok("fuzzy_engine_interface",65);

    int shmid = shmget(key,sizeof(FEI),0666 | IPC_CREAT);

    shmctl(shmid,IPC_RMID,NULL);    

}

void FuzzyEngineInterface::read_memory()
{
    key_t key = ftok("fuzzy_engine_interface",65);

    int shmid = shmget(key,sizeof(FEI),0666 | IPC_CREAT);

    FEI* data = (FEI*)shmat(shmid,(void*)0,0);

    fuzzy_engine_interface = *data;

    shmdt(data);

    
}

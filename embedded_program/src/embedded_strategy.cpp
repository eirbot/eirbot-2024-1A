#include "embedded_strategy.h"
#include "task_queue.h"



void allerRetour(){
    enqueueInstruction({'w', 0.5});
    enqueueInstruction({'f', 50.0});
    enqueueInstruction({'w', 0.5});
    enqueueInstruction({'b', 50.0});
}

void carre(){
    enqueueInstruction({'w', 0.5});
    enqueueInstruction({'f', 70});
    enqueueInstruction({'w', 0.5});
    enqueueInstruction({'r', 3.14/2});

    enqueueInstruction({'w', 0.5});
    enqueueInstruction({'f', 70});
    enqueueInstruction({'w', 0.5});
    enqueueInstruction({'r', 3.14/2});

    enqueueInstruction({'w', 0.5});
    enqueueInstruction({'f', 70});
    enqueueInstruction({'w', 0.5});
    enqueueInstruction({'r', 3.14/2});
    
    enqueueInstruction({'w', 0.5});
    enqueueInstruction({'f', 70});
    enqueueInstruction({'w', 0.5});
    enqueueInstruction({'r', 3.14/2});
}


void ramenerLesPots(){

    enqueueInstruction({'w', 5});

    enqueueInstruction({'f', 120});
    enqueueInstruction({'w', 0.5});

    enqueueInstruction({'r', 3.14/2});
    enqueueInstruction({'w', 0.5});

    enqueueInstruction({'f', 75.8});
    enqueueInstruction({'w', 0.5});

    enqueueInstruction({'r', 2.129});
    enqueueInstruction({'w', 0.5});

    enqueueInstruction({'f', 130});
    enqueueInstruction({'s', 0});
    enqueueInstruction({'e', 0});
}

void inspectEnvironmentAndComputeNewStrategy()
{
    //TODO: enqueue a cyclic instruction
    ramenerLesPots();
};
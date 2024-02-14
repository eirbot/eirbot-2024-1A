#include "embedded_strategy.h"
#include "task_queue.h"

void inspectEnvironmentAndComputeNewStrategy()
{
    //TODO: enqueue a cyclic instruction
    enqueueInstruction({'f', 10});
    enqueueInstruction({'w', 2});
    enqueueInstruction({'b', 10});
    enqueueInstruction({'w', 2});
    // enqueueInstruction({'r', 1});
    // enqueueInstruction({'l', 1});
    // enqueueInstruction({'w', 7000});
};
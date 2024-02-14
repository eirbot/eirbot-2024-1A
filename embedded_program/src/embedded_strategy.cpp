#include "embedded_strategy.h"
#include "task_queue.h"

void inspectEnvironmentAndComputeNewStrategy()
{
    //TODO: enqueue a cyclic instruction
    enqueueInstruction({'f', 1000});
    enqueueInstruction({'b', 1000});
    enqueueInstruction({'r', 100});
    enqueueInstruction({'l', 100});
    // enqueueInstruction({'w', 7000});
};
#include "embedded_strategy.h"
#include "task_queue.h"

void inspectEnvironmentAndComputeNewStrategy()
{
    //TODO: enqueue a cyclic instruction
    enqueueInstruction({'f', 5});
    enqueueInstruction({'f', -5});
    // enqueueInstruction({'w', 7000});
};
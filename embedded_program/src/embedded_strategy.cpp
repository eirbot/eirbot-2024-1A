#include "embedded_strategy.h"
#include "task_queue.h"

void inspectEnvironmentAndComputeNewStrategy()
{
    //TODO: enqueue a cyclic instruction
    enqueueInstruction({'f', 50});
    enqueueInstruction({'r', 3.14159});

    // enqueueInstruction({'w', 7000});
};
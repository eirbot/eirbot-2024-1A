#include "strategy_interface.h"
#include "instruction.h"
#include "embedded_strategy.h"

#define YES 1
#define NO 0

void updateStrategicData(struct instruction justDequeuedInstruction)
{
    switch (justDequeuedInstruction.instruction_type)
    {
    case FORWARD:
        updateNextValuedPosition(justDequeuedInstruction.value, YES);
        break;
    case BACKWARD:
        updateNextValuedPosition(justDequeuedInstruction.value, NO);
        break;
    case TRIG_ROTATE:
        updateNextValuedOrientation(justDequeuedInstruction.value, YES);
        break;
    case NON_TRIG_ROTATE:
        updateNextValuedOrientation(justDequeuedInstruction.value, NO);
        break;
    // TODO: manage the instruction in step number !!!!
    default:
        break;
    }
}
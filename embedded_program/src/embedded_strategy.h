#ifndef __EMBEDDED_STRATEGY_H__
#define __EMBEDDED_STRATEGY_H__

#include "instruction.h"

/**
 * Generate a range of instructions and enqueued it to the
 * task queue. The decision-making algorithm is based on
 * robot's sensorial data.
*/
void inspectEnvironmentAndComputeNewStrategy();

#endif
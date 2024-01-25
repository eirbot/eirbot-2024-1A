#ifndef __SIGNALS_H__
#define __SIGNALS_H__

#include "instruction.h"

/**
 * Returns 1 if an external emergency stop signal has been received, 0 else.
*/
char gotEmergencyStopSignal();

/**
 * Function to be used if the decision-making is computed by an external unit.
 * This function checks if the external unit has sent a range of new instructions.
 * If it is so, then the queue will be cleared and replaced by the received sequence.
*/
void processExternalInstructions();

#endif
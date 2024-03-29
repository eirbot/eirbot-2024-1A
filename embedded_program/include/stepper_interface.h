#ifndef __STEPPER_INTERFACE_H__
#define __STEPPER_INTERFACE_H__

#include "instruction.h"

void initiateBoardVars();
void setMotorsSteps(struct instruction instrct);
void executeOneMotorStep();
char isStepperFree();
void abortRunningTask();

#endif
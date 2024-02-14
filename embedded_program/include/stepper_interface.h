#ifndef __STEPPER_INTERFACE_H__
#define __STEPPER_INTERFACE_H__
#define EMERGENCY_PIN D7

#include "instruction.h"

void initiateBoardVars();
void setMotorsSteps(struct instruction instrct);
void executeOneMotorStep();
char isStepperFree();
void abortRunningTask();

#endif
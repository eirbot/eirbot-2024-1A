#ifndef __VARIABLES_H__
#define __VARIABLES_H__

enum variableName{
    forward = 1,
    manual = 2,
    wait = 3
};

void changeVar(enum variableName variableName, int value);
int checkVar(enum variableName variableName);

#endif
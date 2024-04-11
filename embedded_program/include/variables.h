#ifndef __VARIABLES_H__
#define __VARIABLES_H__

enum variableName{
    forward = 1,
    manual = 2,
    instruct = 3,
    team = 4
};

#define blue 0
#define yellow 1

void changeVar(enum variableName variableName, int value);
int checkVar(enum variableName variableName);

#endif
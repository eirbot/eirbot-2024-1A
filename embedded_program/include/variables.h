#ifndef __VARIABLES_H__
#define __VARIABLES_H__

enum variableName{
    forward = 1,
    manual = 2,
    instruct = 3,
    team = 4,
    match = 5,
    capt = 6
};

#define blue 0
#define yellow 1

#define off 0
#define on 1

#define stratCarre 1
#define aller_retour 2
#define drag 3
// #define stratTest 4

void changeVar(enum variableName variableName, int value);
int checkVar(enum variableName variableName);

#endif
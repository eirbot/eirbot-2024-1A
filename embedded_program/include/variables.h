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

#define stratReact 1
#define strat6P 2
#define strat3P 3

void changeVar(enum variableName variableName, char value);
char checkVar(enum variableName variableName);

#endif
#include "variables.h"
#include "printing.h"

char forwardVal = 1;
char manualVal = 0;
char instructVal = 0;
char teamVal = yellow;
char matchVal = 1;
char captVal = on;

void changeVar(enum variableName variableName, char value){
    switch(variableName){
        case forward:
        {
            forwardVal = value;
        }
        break;

        case manual:
        {
            manualVal = value;
        }
        break;

        case instruct:
        {
            instructVal = value;
        }
        break;

        case team:
        {
            teamVal = value;
        }
        break;

        case match:
        {
            matchVal = value;
        }
        break;

        case capt:
        {
            captVal = value;
        }
        break;

        default:
        printingStr("Wrong variable name in changeVar");
    }
}

char checkVar(enum variableName variableName){
    switch(variableName){
        case 1:
        {
            return forwardVal;
        }
        break;

        case 2:
        {
            return manualVal;
        }
        break;

        case 3:
        {
            return instructVal;
        }
        break;

        case 4:
        {
            return teamVal;
        }
        break;

        case match:
        {
            return matchVal;
        }
        break;

        case capt:
        {
            return captVal;
        }
        break;

        default:
        printingStr("Wrong variable name in checkVar");
    }
    return -1;
}
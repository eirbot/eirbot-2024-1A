#include "variables.h"
#include "printing.h"

char forwardVal = 1;
char manualVal = 0;

void changeVar(enum variableName variableName, int value){
    switch(variableName){
        case 1:
        {
            forwardVal = value;
        }
        break;

        case 2:
        {
            manualVal = value;
        }
        break;

        default:
        printing("Wrong variable name in changeVar");
    }
}

int checkVar(enum variableName variableName){
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

        default:
        printing("Wrong variable name in checkVar");
    }
    return -1;
}
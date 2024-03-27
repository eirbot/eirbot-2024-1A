#include "variables.h"
#include "printing.h"

char forwardVal = 1;
char manualVal = 0;
char waitVal = 0;

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

        case 3:
        {
            waitVal = value;
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

        case 3:
        {
            return waitVal;
        }
        break;

        default:
        printing("Wrong variable name in checkVar");
    }
    return -1;
}
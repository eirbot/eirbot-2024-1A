#include "signals.h"
#include "Arduino.h"
#define EMERGENCY_PIN D7

char gotEmergencyStopSignal()
{
    if (digitalRead(EMERGENCY_PIN))
        return 1;
    return 0;
}

void processExternalInstructions()
{
    //TODO
}

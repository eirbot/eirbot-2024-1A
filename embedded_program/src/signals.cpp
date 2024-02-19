#include "signals.h"
#include "sensors.h"
#include "Arduino.h"
#include "printing.h"
// #define EMERGENCY_PIN D7

char gotEmergencyStopSignal()
{
    // if (digitalRead(EMERGENCY_PIN))
    //     return 1;
    return 0;
}

void processExternalSignals()
{
    int distance = readUltrasonic();
    printing(distance);
}

void processExternalInstructions(){};
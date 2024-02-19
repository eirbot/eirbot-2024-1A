#include "signals.h"
#include "sensors.h"
#include "Arduino.h"
#include "printing.h"
#include "pins.h"

char gotEmergencyStopSignal()
{
    // if (digitalRead(EMERGENCY_PIN))
    //     return 1;
    return 0;
}

void processExternalSignals()
{
    // int distance = readUltrasonic();
    // printing(distance);
}

void processExternalInstructions(){};
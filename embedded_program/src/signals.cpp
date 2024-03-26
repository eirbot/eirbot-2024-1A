#include "sensors.h"
#include "Arduino.h"
#include "printing.h"
#include "pins.h"
#include "task_queue.h"
#include "variables.h"
#include "oled_screen.h"
#include "steppers.h"
#include "stepper_interface.h"

// extern "C++" {
    #include "signals.h"
// }

char gotEmergencyStopSignal()
{
    // if (digitalRead(EMERGENCY_PIN))
    //     return 1;
    return 0;
}

void processExternalSignals()
{
    float distance;
    if (checkVar(forward)){
        distance = readUltrasonic('f');
    }
    else{
        distance = readUltrasonic('b');
    } 
    int posL = motorPos(left);
    int posR = motorPos(right);

    int par = motorPar(left);

    if (distance < 10 && distance > 0.1){
        abortRunningTask();
        enqueueInstruction({'w', 1.0});
    }

    oledPrintln(checkVar(forward), 15, 0);
    oledPrintln(distance, 30, 0);
    oledPrintln(posR, 45, 0);
    oledPrintln(posL, 60, 0);
    oledPrintln(par, 15, 64);
}

void processExternalInstructions(){
    if(Serial.available()){
        char message = Serial.read();
        printing(message);
        oledPrintln("message sent :", 15, 0);
        oledPrintln(message, 50, 0);
        enqueueInstruction({'f', (float) message});
        enqueueInstruction({'w', 0.5});
    }
};
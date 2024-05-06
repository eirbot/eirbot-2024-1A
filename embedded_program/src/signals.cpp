#include "sensors.h"
#include "Arduino.h"
#include "printing.h"
#include "pins.h"
#include "task_queue.h"
#include "variables.h"
#include "oled_screen.h"
#include "steppers.h"
#include "stepper_interface.h"
#include "signals.h"


char gotEmergencyStopSignal()
{
    // if (digitalRead(EMERGENCY_PIN))
    //     return 1;
    return 0;
}

void processExternalSignals()
{
    float distance;
    for(int i=1; i<4; i++){
        if (checkVar(forward)){
            distance = readUltrasonic('f', i);
        }
        else{
            distance = readUltrasonic('b', i);
        } 
        // int posL = motorPos(left);
        // int posR = motorPos(right);

        // int par = motorPar(left);

        // printingFloat(distance);

        if (distance < 30 && distance > 0.1 /*&& (checkVar(instruct) == 'f' || checkVar(instruct) == 'b')*/){
            unsigned int remainingSteps = abortRunningTask();
            pushInstruction({switchInstuct((char) checkVar(instruct)), (float) remainingSteps});
            pushInstruction({'w', 1.0});
            break;
        }

        // oledPrintln((char) checkVar(instruct), 15, 0);
        oledPrintln(distance, 15*i + 15, 0);
        // oledPrintln(posR, 45, 0);
        // oledPrintln(posL, 60, 0);
        // oledPrintln(par, 15, 64);
        
    }
}

void processExternalInstructions(){
    // if(Serial.available()){
    //     char message = Serial.read();
    //     printing(message);
    //     oledPrintln("message sent :", 15, 0);
    //     oledPrintln(message, 50, 0);
    //     enqueueInstruction({'f', (float) message});
    //     enqueueInstruction({'w', 0.5});
    // }
};
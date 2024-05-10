#include <Arduino.h>
#include "sensors.h"
#include "printing.h"
#include "pins.h"
#include "constants.h"
#include <task_queue.h>
#include "variables.h"
#include "stepper_interface.h"
#include "strategy_interface.h"
#include "signals.h"


char gotEmergencyStopSignal()
{
    return 0;
}

void processExternalSignals()
{
    struct instruction currentInstruction = {checkVar(instruct), 0};
    if (checkVar(capt) != off && !canExecuteInstruction(&currentInstruction)) {
        void scheduleDeviationDuringMovement(const struct instruction *interruptedInstr);
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
#include "instruction.h"
#include "stepper_interface.h"
#include "task_queue.h"
#include "embedded_strategy.h"
#include "signals.h"
#include "Arduino.h"

const unsigned int MAX_SEQUENCE_LENGTH = 200;


void processOutsideSignals()
{
    if (gotEmergencyStopSignal()) {
        Serial.println("oui");
        abortRunningTask();
        struct instruction wait = {'w', 2.0}; // Wait 2 seconds
        clearQueue();
        enqueueInstruction(wait);
        // char w=0;
        // while(!w){
        //     Serial.println(digitalRead(D7));
        // }
    } else
        processExternalSignals();
        processExternalInstructions();
}

void scheduleNextInstruction()
{
    if (isQueueEmpty())
        inspectEnvironmentAndComputeNewStrategy();
    setMotorsSteps(dequeueInstruction());
}

const unsigned int DELTA_T = 50; // Each time the board will inspect the received signals
unsigned int t = 0;

void setup()
{
    initiateBoardVars();
    t = 0;
    Serial.begin(9600);
    // Serial1.begin(9600);
    // pinMode(A0, INPUT);
}

void loop()
{
    if (t++ == DELTA_T) {
        t = 0;
        processOutsideSignals();
    }
    if (isStepperFree())
        scheduleNextInstruction();
    executeOneMotorStep();
}
#include "stepper_interface.h"
#include "steppers.h"
#include "conversions.h"
#include "Arduino.h"
#include "pins.h"
#include "variables.h"
#include "printing.h"
#include "oled_screen.h"

#define DELAY_PER_STEP 20 // 0.02s

unsigned int remaining_time; // multiple of 0.2s
// the expected total number of steps achieved by the left wheel after the current instruction
unsigned int scheduledStepNumberL;
// the expected total number of steps achieved by the right wheel after the current instruction
unsigned int scheduledStepNumberR;

void initiateBoardVars()
{
    remaining_time = 0;
    scheduledStepNumberL = 0;
    scheduledStepNumberR = 0;
    pinMode(trigPin, OUTPUT);
    pinMode(echoPinF, INPUT);
    pinMode(echoPinB, INPUT);
    pinMode(D9, OUTPUT);
    digitalWrite(D9, LOW);
    // pinMode(EMERGENCY_PIN, INPUT);
    // digitalWrite(EMERGENCY_PIN, LOW);
    board_setup();
    oled_setup();
    // changeVar(manual, 1);
}

void setMotorsSteps(struct instruction instrct)
{
    struct wheel_step_data left_wheel_data;
    struct wheel_step_data right_wheel_data;
    switch (instrct.instruction_type) {
        case 'f':
        {
            set_wheels_rotation_from_distance(instrct.value, &left_wheel_data, &right_wheel_data);
            changeVar(forward, 1);
            changeVar(wait, 0);
            motorSetHome(right);
            motorSetHome(left);
            avancer(right_wheel_data.step_number);
        }
            break;
        case 'b':
        {
            set_wheels_rotation_from_distance(instrct.value, &left_wheel_data, &right_wheel_data);
            changeVar(forward, 0);
            changeVar(wait, 0);
            motorSetHome(right);
            motorSetHome(left);
            reculer(right_wheel_data.step_number);
        }
            break;
        case 'r':
        {
            set_wheels_rotation_from_global_rotation(instrct.value, &left_wheel_data, &right_wheel_data);
            tournerDroite(left_wheel_data.step_number, right_wheel_data.step_number);
            changeVar(wait, 0);
            motorSetHome(right);
            motorSetHome(left);
        }
            break;
        case 'l':
        {
            set_wheels_rotation_from_global_rotation(instrct.value, &left_wheel_data, &right_wheel_data);
            tournerGauche(left_wheel_data.step_number, right_wheel_data.step_number);
            changeVar(wait, 0);
            motorSetHome(right);
            motorSetHome(left);
        }
            break;
        case 's':
        {
            setSpeed(instrct.value);
            changeVar(wait, 0);
        }
            break;
        case 'w':
        {
            remaining_time = instrct.value * (1000/DELAY_PER_STEP);
            changeVar(wait, 1);
        }
            break;
        case 'e':
        {
            while(1);
        }
        break;

        case '1':
        {
            right_wheel_data.step_number = (unsigned int) instrct.value;
            changeVar(forward, 1);
            changeVar(wait, 0);
            motorSetHome(right);
            motorSetHome(left);
            avancer(right_wheel_data.step_number);
        }
            break;
        case '2':
        {
            right_wheel_data.step_number = (unsigned int) instrct.value;
            changeVar(forward, 0);
            changeVar(wait, 0);
            motorSetHome(right);
            motorSetHome(left);
            reculer(right_wheel_data.step_number);
        }
            break;
        case '3':
        {
            right_wheel_data.step_number = (unsigned int) instrct.value;
            left_wheel_data.step_number = (unsigned int) instrct.value;
            tournerDroite(left_wheel_data.step_number, right_wheel_data.step_number);
            changeVar(wait, 0);
            motorSetHome(right);
            motorSetHome(left);
        }
            break;
        case '4':
        {
            right_wheel_data.step_number = (unsigned int) instrct.value;
            left_wheel_data.step_number = (unsigned int) instrct.value;
            tournerGauche(left_wheel_data.step_number, right_wheel_data.step_number);
            changeVar(wait, 0);
            motorSetHome(right);
            motorSetHome(left);
        }
        
        default:
            break;
    }
    scheduledStepNumberL = left_wheel_data.step_number;
    scheduledStepNumberR = left_wheel_data.step_number;
    
}

void executeOneMotorStep()
{
    // motor_step();
    if (remaining_time){
        remaining_time--;
        delay(DELAY_PER_STEP);
    }
}

char isStepperFree()
{
    if (!remaining_time)
        return motor_free();
    else
        return 0;
}

int abortRunningTask()
{
    hardStop();
    int posL = motorPos(left);
    int posR = motorPos(right);
    return scheduledStepNumberR - posR;
}
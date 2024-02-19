#include "stepper_interface.h"
#include "steppers.h"
#include "conversions.h"
#include "Arduino.h"

#define DELAY_PER_STEP 200 // 0.2s

unsigned int remaining_time; // multiple of 0.2s 

void initiateBoardVars()
{
    remaining_time = 0;
    pinMode(EMERGENCY_PIN, INPUT);
    digitalWrite(EMERGENCY_PIN, LOW);
    board_setup();
}

void setMotorsSteps(struct instruction instrct)
{
    struct wheel_step_data left_wheel_data;
    struct wheel_step_data right_wheel_data;
    switch (instrct.instruction_type) {
        case 'f':
        {
            set_wheels_rotation_from_distance(instrct.value, &left_wheel_data, &right_wheel_data);
            avancer(right_wheel_data.step_number);
        }
            break;
        case 'b':
        {
            set_wheels_rotation_from_distance(instrct.value, &left_wheel_data, &right_wheel_data);
            reculer(right_wheel_data.step_number);
        }
            break;
        case 'r':
        {
            set_wheels_rotation_from_global_rotation(instrct.value, &left_wheel_data, &right_wheel_data);
            tournerDroite(left_wheel_data.step_number, right_wheel_data.step_number);
        }
            break;
            case 'l':
        {
            set_wheels_rotation_from_global_rotation(instrct.value, &left_wheel_data, &right_wheel_data);
            tournerGauche(left_wheel_data.step_number, right_wheel_data.step_number);
        }
            break;
        {
        case 'w':
            remaining_time = instrct.value * (1000/DELAY_PER_STEP);
        }
            break;
        
        default:
            break;
    }
    
}

void executeOneMotorStep()
{
    // motor_step();
    if (remaining_time)
        remaining_time--;
    delay(DELAY_PER_STEP);
}

char isStepperFree()
{
    if (!remaining_time)
        return motor_free();
    else
        return 0;
}

void abortRunningTask()
{
    hardStop();
}
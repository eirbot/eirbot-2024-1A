#include "stepper_interface.h"
#include "steppers.h"
#include "conversions.h"

void initiateBoardVars()
{
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
            unsigned int milliseconds = (instrct.value>=0)?instrct.value:-instrct.value;
        }
            break;
        
        default:
            break;
    }
    
}

void executeOneMotorStep()
{
    // motor_step();
}

char isStepperFree()
{
    return motor_free();
}

void abortRunningTask()
{
    hardStop();
}
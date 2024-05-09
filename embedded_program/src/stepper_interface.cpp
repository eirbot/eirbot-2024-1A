#include <Arduino.h>

#include "stepper_interface.h"
#include "steppers.h"
#include "conversions.h"
#include "pins.h"
#include "variables.h"
#include "printing.h"
#include "oled_screen.h"
#include "instruction.h"
#include "sensors.h"

#define DELAY_PER_STEP 20 // 0.02s

// #define d300 45
// #define d90 150

#define d300 50
#define d90 150

unsigned int remaining_time; // multiple of 0.2s
// the expected total number of steps achieved by the left wheel after the current instruction
int scheduledStepNumberL;
// the expected total number of steps achieved by the right wheel after the current instruction
int scheduledStepNumberR;

void initiateBoardVars()
{
    remaining_time = 0;
    scheduledStepNumberL = 0;
    scheduledStepNumberR = 0;
    pinMode(trigPinM, OUTPUT);
    pinMode(trigPinL, OUTPUT);
    pinMode(trigPinR, OUTPUT);

    pinMode(echoPinFM, INPUT);
    pinMode(echoPinFL, INPUT);
    pinMode(echoPinFR, INPUT);
    
    pinMode(echoPinBM, INPUT);
    pinMode(echoPinBL, INPUT);
    pinMode(echoPinBR, INPUT);

    pinMode(servoPin, OUTPUT);
    pinMode(tirettePin, INPUT_PULLUP);

    pinMode(BTNC, INPUT_PULLUP);
    pinMode(BTN1, INPUT_PULLUP);
    pinMode(BTN2, INPUT_PULLUP);
    pinMode(BTN3, INPUT_PULLUP);
    pinMode(BTN4, INPUT_PULLUP);
    // pinMode(EMERGENCY_PIN, INPUT);
    // digitalWrite(EMERGENCY_PIN, LOW);
    board_setup();
    oled_setup();
    // changeVar(manual, 1);
    oledPrintln("Demarage...", 15,  0);
}

void setMotorsSteps(struct instruction instrct)
{
    struct wheel_step_data left_wheel_data;
    struct wheel_step_data right_wheel_data;

    motorSetHome(right);
    motorSetHome(left);
    
    switch (instrct.instruction_type) {
        case 'f':
        {
            set_wheels_rotation_from_distance(instrct.value, &left_wheel_data, &right_wheel_data);
            changeVar(forward, 1);
            avancer(right_wheel_data.step_number, d300);
        }
            break;
        case 'b':
        {
            set_wheels_rotation_from_distance(instrct.value, &left_wheel_data, &right_wheel_data);
            changeVar(forward, 0);
            reculer(right_wheel_data.step_number, d300);
        }
            break;
        case 'g':
        {
            set_wheels_rotation_from_distance(instrct.value, &left_wheel_data, &right_wheel_data);
            changeVar(forward, 1);
            avancer(right_wheel_data.step_number, d90);
        }
            break;
        case 'h':
        {
            set_wheels_rotation_from_distance(instrct.value, &left_wheel_data, &right_wheel_data);
            changeVar(forward, 0);
            reculer(right_wheel_data.step_number, d90);
        }
            break;
        // case 'f':
        // {
        //     set_wheels_rotation_from_distance(instrct.value, &left_wheel_data, &right_wheel_data);
        //     changeVar(forward, 1);
        //     avancerVit();
        // }
        //     break;
        // case 'b':
        // {
        //     set_wheels_rotation_from_distance(instrct.value, &left_wheel_data, &right_wheel_data);
        //     changeVar(forward, 0);
        //     reculerVit();
        // }
        //     break;
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
        case 's':
        {
            setSpeed(instrct.value);
        }
            break;
        case 'p':
        {
            setServo(instrct.value);
            remaining_time = 1 * (1000/DELAY_PER_STEP);
        }
            break;
        case 'w':
        {
            remaining_time = instrct.value * (1000/DELAY_PER_STEP);
        }
            break;
        case 'e':
        {
            while(1);
        }
            break;
            case 'a':
        {
            // while(digitalRead(tirettePin));
        }
            break;
        case '1':
        {
            right_wheel_data.step_number = (unsigned int) instrct.value;
            changeVar(forward, 1);
            avancer(right_wheel_data.step_number, d300);
        }
            break;
        case '2':
        {
            right_wheel_data.step_number = (unsigned int) instrct.value;
            changeVar(forward, 0);
            reculer(right_wheel_data.step_number, d300);
        }
            break;
        case '3':
        {
            right_wheel_data.step_number = (unsigned int) instrct.value;
            left_wheel_data.step_number = (unsigned int) instrct.value;
            tournerDroite(left_wheel_data.step_number, right_wheel_data.step_number);
        }
            break;
        case '4':
        {
            right_wheel_data.step_number = (unsigned int) instrct.value;
            left_wheel_data.step_number = (unsigned int) instrct.value;
            tournerGauche(left_wheel_data.step_number, right_wheel_data.step_number);
        }
            break;
        case '5':
        {
            right_wheel_data.step_number = (unsigned int) instrct.value;
            changeVar(forward, 1);
            avancer(right_wheel_data.step_number, d90);
        }
            break;
        case '6':
        {
            right_wheel_data.step_number = (unsigned int) instrct.value;
            changeVar(forward, 0);
            reculer(right_wheel_data.step_number, d90);
        }
        
        default:
            break;
    }
    changeVar(instruct, instrct.instruction_type);
    scheduledStepNumberL = left_wheel_data.step_number;
    scheduledStepNumberR = right_wheel_data.step_number;
    // oledPrintln(instrct.instruction_type, 15, 0);
    // oledPrint(scheduledStepNumberR, 15, 35);
    
}

void executeOneMotorStep()
{
    if (remaining_time){
        remaining_time--;
        delay(DELAY_PER_STEP);
    }
}

char isStepperFree()
{
    // if(checkVar(instruct) == 'f' || checkVar(instruct) == 'b'){
    //     int mpos = motorPos(right);
    //     oledPrintln(mpos, 60, 0);
    //     if(abs(mpos) + 820 >= scheduledStepNumberR){
    //         pushInstruction({'s', 0});
    //         return 1;
    //     }
    // }
    // else {
        if(!remaining_time /*&& motorSpeed(right) < 5*/) return motor_free();
    // }
    
    return 0;
}

int abortRunningTask()
{
    hardStop();
    int posL = motorPos(left);
    int posR = motorPos(right);
    return abs(scheduledStepNumberR - abs(posR));
}

char switchInstuct(char instructVal){
    switch(instructVal){
        case 'f':
        return '1';
        break;

        case 'b':
        return '2';
        break;

        case 'r':
        return '3';
        break;

        case 'l':
        return '4';
        break;

        case 'g':
        return '5';
        break;

        case 'h':
        return '6';
        break;
        
        default:
        return instructVal;
    }
}

void interface(){
    char LRM = 1;
    while(!digitalRead(tirettePin)){

        if(digitalRead(BTN1) && checkVar(team) == blue){
            changeVar(team, yellow);
        }
        if(!digitalRead(BTN1) && checkVar(team) == yellow){
            changeVar(team, blue);
        }

        oledPrintln(checkVar(team)? "equ jaune" : "equ bleue",15, 0);

        if(!digitalRead(BTN2) && checkVar(forward)) {
            changeVar(forward, 0);
            oledBlink(50);
        }
        if(digitalRead(BTN2) && !checkVar(forward)) {
            changeVar(forward, 1);
            oledBlink(50);
        }

        if(digitalRead(BTN3)){

            float distance;
            for(int i=1; i<4; i++){
                distance = readUltrasonic(checkVar(forward)? 'f' : 'b', i);
                oledPrintln(distance, 15*i + 15, 0);
            }
        }
        else{
            // oledRefresh();
            float distance = readUltrasonic(checkVar(forward)? 'f' : 'b', LRM);
            oledPrintln(distance, 30, 0);
            oledPrintln((float) LRM, 45, 0);
        }

        if(!digitalRead(BTNC)){
            while(!digitalRead(BTNC));
            LRM ++;
            if(LRM == 4) LRM = 1;
        }        

        if(digitalRead(BTN4)){
            setServo(7);
            // while(digitalRead(BTN4));
            // struct wheel_step_data pas;
            // set_wheels_rotation_from_distance(50, &pas, &pas);
            // avancer(pas.step_number);
            // while(!motor_free);
            // reculer(pas.step_number);
            // while(!motor_free);
        }
        else{
            setServo(105);
        }

        oledBlink(20);
    }
    oledRefresh();
}
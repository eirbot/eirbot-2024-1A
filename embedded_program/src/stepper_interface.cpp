#include "stepper_interface.h"
#include "steppers.h"
#include "conversions.h"
#include "Arduino.h"
#include "pins.h"
#include "variables.h"
#include "printing.h"
#include "oled_screen.h"
#include "task_queue.h"
#include "sensors.h"

#define DELAY_PER_STEP 20 // 0.02s

// #define d300 45
// #define d90 150

#define d300 38
#define d90 90

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
            char ok = 1;
            float distance;
            for(int i=1; i<4; i++){
                distance = readUltrasonic('f', i);
                
                if (distance < 17 && distance > 0.1 /*&& (checkVar(instruct) == 'f' || checkVar(instruct) == 'b')*/){
                    ok = 0;
                    break;
                }
            }
            if(ok){
                set_wheels_rotation_from_distance(instrct.value, &left_wheel_data, &right_wheel_data);
                changeVar(forward, 1);
                avancer(right_wheel_data.step_number, d300);
            }
            else{
                pushInstruction({instrct.instruction_type, instrct.value});
            }
        }
            break;
        case 'b':
        {
            char ok = 1;
            float distance;
            for(int i=1; i<4; i++){
                distance = readUltrasonic('b', i);
                
                if (distance < 17 && distance > 0.1 /*&& (checkVar(instruct) == 'f' || checkVar(instruct) == 'b')*/){
                    ok = 0;
                    break;
                }
            }
            if(ok){
                set_wheels_rotation_from_distance(instrct.value, &left_wheel_data, &right_wheel_data);
                changeVar(forward, 0);
                reculer(right_wheel_data.step_number, d300);
            }
            else{
                pushInstruction({instrct.instruction_type, instrct.value});
            }
        }
            break;
        case 'g':
        {
            char ok = 1;
            float distance;
            for(int i=1; i<4; i++){
                distance = readUltrasonic('f', i);
                
                if (distance < 17 && distance > 0.1 /*&& (checkVar(instruct) == 'f' || checkVar(instruct) == 'b')*/){
                    ok = 0;
                    break;
                }
            }
            if(ok){
                set_wheels_rotation_from_distance(instrct.value, &left_wheel_data, &right_wheel_data);
                changeVar(forward, 1);
                avancer(right_wheel_data.step_number, d90);
            }
            else{
                pushInstruction({instrct.instruction_type, instrct.value});
            }
        }
            break;
        case 'h':
        {
            char ok = 1;
            float distance;
            for(int i=1; i<4; i++){
                distance = readUltrasonic('b', i);
                
                if (distance < 17 && distance > 0.1 /*&& (checkVar(instruct) == 'f' || checkVar(instruct) == 'b')*/){
                    ok = 0;
                    break;
                }
            }
            if(ok){
                set_wheels_rotation_from_distance(instrct.value, &left_wheel_data, &right_wheel_data);
                changeVar(forward, 0);
                reculer(right_wheel_data.step_number, d90);
            }
            else{
                pushInstruction({instrct.instruction_type, instrct.value});
            }
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
            char ok = 1;
            float distance;

            distance = readUltrasonic('f', 1);
            
            if (distance < 17 && distance > 0.1 /*&& (checkVar(instruct) == 'f' || checkVar(instruct) == 'b')*/){
                ok = 0;
            }

            distance = readUltrasonic('b', 2);
            
            if (distance < 17 && distance > 0.1 /*&& (checkVar(instruct) == 'f' || checkVar(instruct) == 'b')*/){
                ok = 0;
            }
            
            if(ok){
                set_wheels_rotation_from_global_rotation(instrct.value, &left_wheel_data, &right_wheel_data);
                tournerDroite(left_wheel_data.step_number, right_wheel_data.step_number);
            }
            else{
                pushInstruction({instrct.instruction_type, instrct.value});
            }
        }
            break;
        case 'l':
        {
            char ok = 1;
            float distance;
            distance = readUltrasonic('f', 2);
            
            if (distance < 17 && distance > 0.1 /*&& (checkVar(instruct) == 'f' || checkVar(instruct) == 'b')*/){
                ok = 0;
            }

            distance = readUltrasonic('b', 1);
            
            if (distance < 17 && distance > 0.1 /*&& (checkVar(instruct) == 'f' || checkVar(instruct) == 'b')*/){
                ok = 0;
            }

            if(ok){
                set_wheels_rotation_from_global_rotation(instrct.value, &left_wheel_data, &right_wheel_data);
                tournerGauche(left_wheel_data.step_number, right_wheel_data.step_number);
            }
            else{
                pushInstruction({instrct.instruction_type, instrct.value});
            }            
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
            char ok = 1;
            float distance;
            for(int i=1; i<4; i++){
                distance = readUltrasonic('f', i);
                
                if (distance < 17 && distance > 0.1 /*&& (checkVar(instruct) == 'f' || checkVar(instruct) == 'b')*/){
                    ok = 0;
                    break;
                }
            }
            if(ok){
                right_wheel_data.step_number = (unsigned int) instrct.value;
                changeVar(forward, 1);
                avancer(right_wheel_data.step_number, d300);
            }
            else{
                pushInstruction({instrct.instruction_type, instrct.value});
                pushInstruction({'w', 0.2});
            }
        }
            break;
        case '2':
        {
            char ok = 1;
            float distance;
            for(int i=1; i<4; i++){
                distance = readUltrasonic('b', i);
                
                if (distance < 17 && distance > 0.1 /*&& (checkVar(instruct) == 'f' || checkVar(instruct) == 'b')*/){
                    ok = 0;
                    break;
                }
            }
            if(ok){
                right_wheel_data.step_number = (unsigned int) instrct.value;
                changeVar(forward, 0);
                reculer(right_wheel_data.step_number, d300);
            }
            else{
                pushInstruction({instrct.instruction_type, instrct.value});
            }
        }
            break;
        case '3':
        {
            char ok = 1;
            float distance;

            distance = readUltrasonic('f', 1);
            
            if (distance < 17 && distance > 0.1 /*&& (checkVar(instruct) == 'f' || checkVar(instruct) == 'b')*/){
                ok = 0;
            }

            distance = readUltrasonic('b', 2);
            
            if (distance < 17 && distance > 0.1 /*&& (checkVar(instruct) == 'f' || checkVar(instruct) == 'b')*/){
                ok = 0;
            }
            
            if(ok){
                right_wheel_data.step_number = (unsigned int) instrct.value;
                left_wheel_data.step_number = (unsigned int) instrct.value;
                tournerDroite(left_wheel_data.step_number, right_wheel_data.step_number);
            }
            else{
                pushInstruction({instrct.instruction_type, instrct.value});
            }            
        }
            break;
        case '4':
        {
            char ok = 1;
            float distance;
            distance = readUltrasonic('f', 2);
            
            if (distance < 17 && distance > 0.1 /*&& (checkVar(instruct) == 'f' || checkVar(instruct) == 'b')*/){
                ok = 0;
            }

            distance = readUltrasonic('b', 1);
            
            if (distance < 17 && distance > 0.1 /*&& (checkVar(instruct) == 'f' || checkVar(instruct) == 'b')*/){
                ok = 0;
            }

            if(ok){
                right_wheel_data.step_number = (unsigned int) instrct.value;
                left_wheel_data.step_number = (unsigned int) instrct.value;
                tournerGauche(left_wheel_data.step_number, right_wheel_data.step_number);
            }
            else{
                pushInstruction({instrct.instruction_type, instrct.value});
            }
        }
            break;
        case '5':
        {
            char ok = 1;
            float distance;
            for(int i=1; i<4; i++){
                distance = readUltrasonic('f', i);
                
                if (distance < 17 && distance > 0.1 /*&& (checkVar(instruct) == 'f' || checkVar(instruct) == 'b')*/){
                    ok = 0;
                    break;
                }
            }
            if(ok){
                right_wheel_data.step_number = (unsigned int) instrct.value;
                changeVar(forward, 1);
                avancer(right_wheel_data.step_number, d90);
            }
            else{
                pushInstruction({instrct.instruction_type, instrct.value});
            }
        }
            break;
        case '6':
        {
            char ok = 1;
            float distance;
            for(int i=1; i<4; i++){
                distance = readUltrasonic('b', i);
                
                if (distance < 17 && distance > 0.1 /*&& (checkVar(instruct) == 'f' || checkVar(instruct) == 'b')*/){
                    ok = 0;
                    break;
                }
            }
            if(ok){
                right_wheel_data.step_number = (unsigned int) instrct.value;
                changeVar(forward, 0);
                reculer(right_wheel_data.step_number, d90);
            }
            else{
                pushInstruction({instrct.instruction_type, instrct.value});
            }
        }
            break;
        
        case '7':
        {
            char ok = 1;
            float distance;
            for(int i=1; i<4; i++){
                distance = readUltrasonic('f', i);
                
                if (distance < 17 && distance > 0.1 /*&& (checkVar(instruct) == 'f' || checkVar(instruct) == 'b')*/){
                    ok = 0;
                    break;
                }
            }
            if(ok){
                set_wheels_rotation_from_distance(instrct.value, &left_wheel_data, &right_wheel_data);
                changeVar(forward, 1);
                avancer(right_wheel_data.step_number, d300);
            }
            else{
                pushInstruction({instrct.instruction_type, instrct.value});
            }
        }
            break;
        case '8':
        {
            char ok = 1;
            float distance;
            for(int i=1; i<4; i++){
                distance = readUltrasonic('b', i);
                
                if (distance < 17 && distance > 0.1 /*&& (checkVar(instruct) == 'f' || checkVar(instruct) == 'b')*/){
                    ok = 0;
                    break;
                }
            }
            if(ok){
                set_wheels_rotation_from_distance(instrct.value, &left_wheel_data, &right_wheel_data);
                changeVar(forward, 0);
                reculer(right_wheel_data.step_number, d300);
            }
            else{
                pushInstruction({instrct.instruction_type, instrct.value});
            }
        }
            break;
        
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

        case '6':
        return 'a';
        break;

        case '7':
        return 'a';
        break;
        
        default:
        return instructVal;
    }
}

int interface(){
    // char LRM = 1;
    int score = 33;
    char debugMode = 0;
    char matchMode = 0;
    float distance = 0;
    while(!digitalRead(tirettePin)){

        if(!digitalRead(BTN4)){             // match mode
            if(digitalRead(BTN1) && checkVar(team) == blue){
                changeVar(team, yellow);
            }
            if(!digitalRead(BTN1) && checkVar(team) == yellow){
                changeVar(team, blue);
            }

            oledPrintln(checkVar(team)? "equ jaune" : "equ bleue",15, 0);
            
            if(!digitalRead(BTN3)){
                oledSquare(30, on);
                oledSquare(60, off);

                if(!digitalRead(BTNC)){
                    while(!digitalRead(BTNC));

                    char matchVal = checkVar(match);

                    if(matchVal >= 3) changeVar(match, 1);
                    else changeVar(match, checkVar(match) + 1);

                    oledPrintln(" ", 30, 0);
                }
            }
            else {
                oledSquare(30, off);
                oledSquare(60, on);

                if(!digitalRead(BTNC)){
                    while(!digitalRead(BTNC));

                    score ++;

                    if(score >= 52) score = 15;
                    oledPrintln(" ", 60, 0);
                }
            }

            switch(checkVar(match)){
                case stratReact:
                    oledPrintln("strat react",30, 0);
                    break;
                case strat6P:
                    oledPrintln("strat 6 p",30, 0);
                    break;
                case strat3P:
                    oledPrintln("strat 3 p",30, 0);
                    break;
                default:
                    oledPrintln("wrong strat",30, 0);
                    break;
            }

            if(digitalRead(BTN2) && checkVar(capt) == off){
                changeVar(capt, on);
            }
            if(!digitalRead(BTN2) && checkVar(capt) == on){
                changeVar(capt, off);
            }

            oledPrintln(checkVar(capt)? "capt on" : "capt off", 45, 0);

            // if(digitalRead(BTN3)){
            //     changeVar(match, 0);
            //     float distance;
            //     for(int i=1; i<4; i++){
            //         distance = readUltrasonic(checkVar(forward)? 'f' : 'b', i);
            //         oledPrintln(distance, 15*i + 15, 0);
            //     }
            // }
            // else{
            //     changeVar(match, 1);
            // }
            // oledPrintln(checkVar(match)? "match" : "practice", 30, 0);

            oledPrintln("score ", 60, 0);
            oledPrint(score, 60, 60);
            oledBlink(5);
        }

        else{               // debugMode
            oledPrintln("debug mode", 15, 0);

            if(!digitalRead(BTN1) && checkVar(forward)) {
                changeVar(forward, 0);
            }
            if(digitalRead(BTN1) && !checkVar(forward)) {
                changeVar(forward, 1);
            }

            for(int i=1; i<4; i++){
                distance = readUltrasonic(checkVar(forward)? 'f' : 'b', i);
                oledPrintln(distance, 15*i + 15, 0);
            }

            // if(!digitalRead(BTNC)){
            //     while(!digitalRead(BTNC));
            //     LRM ++;
            //     if(LRM == 4) LRM = 1;
            // }        

            if(digitalRead(BTN3)){
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
            oledBlink(5);
        }
    }
    oledRefresh();
    return score;
}
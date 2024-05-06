#include "Arduino.h"
#include "pins.h"
#include "printing.h"

float readUltrasonic(char FwdBwd, char LRM){

    int trigPin;
    int echoPinF;
    int echoPinB;

    switch(LRM){
        case 1:{
            trigPin = trigPinL;
            echoPinF = echoPinFL;
            echoPinB = echoPinBL;
            break;
        }
        case 2:{
            trigPin = trigPinR;
            echoPinF = echoPinFR;
            echoPinB = echoPinBR;
            break;
        }
        case 3:{
            trigPin = trigPinM;
            echoPinF = echoPinFM;
            echoPinB = echoPinBM;
            break;
        }
    }

    long duration;
    float distance;
    digitalWrite(trigPin, LOW);
    delayMicroseconds(5);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);
    // delayMicroseconds(2);

    if (FwdBwd=='f') duration = pulseIn(echoPinF, HIGH);
    if (FwdBwd=='b') duration = pulseIn(echoPinB, HIGH);
    printingInt(duration);
    distance = (float) duration * 0.034 / 2.0;
    return distance;
}
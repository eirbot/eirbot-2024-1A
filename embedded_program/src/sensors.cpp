#include "Arduino.h"
#include "pins.h"
#include "printing.h"

int readUltrasonic(){
    long duration;
    int distance;
    digitalWrite(trigPin, LOW);
    delayMicroseconds(5);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);
    // delayMicroseconds(2);

    duration = pulseIn(echoPin, HIGH);
    printing(duration);
    distance = duration * 0.034 / 2;
    return distance;
}
#include "Arduino.h"

#define trigPin D6
#define echoPin D7

int readUltrasonic(){
    long duration;
    int distance;
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);

    duration = pulseIn(echoPin, HIGH);
    distance = duration * 0.034 / 2;
    return distance;
}
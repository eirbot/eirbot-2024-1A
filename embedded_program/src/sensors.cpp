#include "Arduino.h"
#include "pins.h"
#include "printing.h"

float readUltrasonic(){
    long duration;
    float distance;
    digitalWrite(trigPin, LOW);
    delayMicroseconds(5);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);
    // delayMicroseconds(2);

    duration = pulseIn(echoPin, HIGH);
    // printing(duration);
    distance = (float) duration * 0.034 / 2.0;
    return distance;
}
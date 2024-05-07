#ifndef MOTOR
#include <iostream>
#include <Arduino.h>

class Motor {
private:
    //args
    int Pin_1;
    int Pin_2;
    int Pin_pwm;
public:
    // Constructor to initialize the motor
    Motor(int Pin_1, int Pin_2, int Pin_pwm) : Pin_1(Pin_1), Pin_2(Pin_2), Pin_pwm(Pin_pwm) {}

    void setPwm(int newPwm, bool sens);
};

#endif
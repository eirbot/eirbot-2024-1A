#include "motor.h"


int Motor::setPwm(int newPwm){
        if (newPwm>0)
        {
            analogWrite(Pin_pwm, newPwm);
            digitalWrite(Pin_1, HIGH);
            digitalWrite(Pin_2, LOW);
        }
        else if (newPwm <= 0)
        {
            analogWrite(Pin_pwm, -newPwm);
            digitalWrite(Pin_1, LOW);
            digitalWrite(Pin_2, HIGH);
        }
        else{
            analogWrite(Pin_pwm, 0);
        }
    return -newPwm;
}

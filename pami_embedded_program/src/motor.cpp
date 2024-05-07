#include "motor.h"


void Motor::setPwm(int newPwm, bool sens){
        if (sens)
        {
            analogWrite(Pin_pwm, newPwm);
            digitalWrite(Pin_1, HIGH);
            digitalWrite(Pin_2, LOW);
        }
        else
        {
            analogWrite(Pin_pwm, newPwm);
            digitalWrite(Pin_1, LOW);
            digitalWrite(Pin_2, HIGH);
        }
}
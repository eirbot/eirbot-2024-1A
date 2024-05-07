#include "captor.h"


int Captor::readSpeed(int T_ech_capt, int previous_1, int previous_2){
    previous_1 += digitalRead(Pin_1);
    previous_2 += digitalRead(Pin_2); 
    int speed = previous_1/T_ech_capt;
    return speed;
}
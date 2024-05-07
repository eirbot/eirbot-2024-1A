
#ifndef CAPTOR
#include <Arduino.h>


class Captor {
private:
    //args
    int Pin_1;
    int Pin_2;
    
public:

    Captor(int Pin_1, int Pin_2) : Pin_1(Pin_1),Pin_2(Pin_2) {}

    int readSpeed(int T_ech_capt, int previous_1, int previous_2);

};


#endif
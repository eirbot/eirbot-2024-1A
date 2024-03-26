#ifndef __STEPPERS_H__
#define __STEPPERS_H__

enum motor{
    left = 1,
    right = 0
};

void board_setup();
void avancer(unsigned int pas);
void reculer(unsigned int pas);
void tournerDroite(int pasG, int pasD);
void tournerGauche(int pasG, int pasD);
void setSpeed(int stepPerSec);
//void schedule_standby(unsigned int delta_t);
char motor_free();
void hardStop();
//void motor_step();
int motorPos(enum motor motor);
int motorPar(enum motor motor);

#endif
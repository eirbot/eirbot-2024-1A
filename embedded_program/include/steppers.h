#ifndef __STEPPERS_H__
#define __STEPPERS_H__

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

#endif
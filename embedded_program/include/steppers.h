#ifndef __STEPPERS_H__
#define __STEPPERS_H__

enum motor{
    left = 1,
    right = 0
};

void board_setup();
void avancer(unsigned int pas);
void avancerVit();
void reculer(unsigned int pas);
void reculerVit();
void tournerDroite(int pasG, int pasD);
void tournerDroiteVit();
void tournerGauche(int pasG, int pasD);
void tournerGaucheVit();
void setSpeed(int stepPerSec);
//void schedule_standby(unsigned int delta_t);
char motor_free();
void hardStop();
//void motor_step();
int motorPos(enum motor motor);
int motorPar(enum motor motor);
void motorSetHome(enum motor motor);
void setServo(char angle);
int motorSpeed(enum motor motor);

#endif
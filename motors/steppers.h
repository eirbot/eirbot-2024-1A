#ifndef __STEPPERS_H__
#define __STEPPERS_H__

void board_setup();
void def_avancerD(unsigned int pas, char dir);
void def_avancerG(unsigned int pas, char dir);
void schedule_standby(unsigned int delta_t);
char motor_free();
void motor_step();

#endif
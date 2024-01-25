#ifndef __STEPPERS_H__
#define __STEPPERS_H__

void board_setup();
void avancer(unsigned int pas);
void reculer(unsigned int pas);
//void schedule_standby(unsigned int delta_t);
//char motor_free();
//void motor_step();

#endif
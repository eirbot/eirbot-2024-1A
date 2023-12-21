#include "steppers.h"

const unsigned int DELAY_BY_STEP_WHILE_STOP = 2000;

// Define pin connections & motor's steps per revolution
// const int pas_r = 500;
const int vit_min = 2500;
const int vit_max = 500;
const int vit_rampe = 6;
// const int delta_r = (vit_min-vit_min)/pas_r;
const int dirPinG = 5;
const int stepPinG = 6;
const int dirPinD = 8;
const int stepPinD = 9;
const int tour = 200;
// unsigned long time = 0;
// unsigned long deltat = 0;

int r_pasD = 0;
int r_dirD = 0;
unsigned long r_timeD = 0;
int r_delaiD = 0;
char r_hlD = 0;
char mot_libreD = 1;
int r_pas_faitsD = 0;
int r_pas_restantsD = 0;

int r_pasG = 0;
int r_dirG = 0;
unsigned long r_timeG = 0;
int r_delaiG = 0;
char r_hlG = 0;
char mot_libreG = 1;
int r_pas_faitsG = 0;
int r_pas_restantsG = 0;

unsigned long a = 0;

void board_setup()
{
    // Declare pins as Outputs
    pinMode(stepPinD, OUTPUT);
    pinMode(dirPinD, OUTPUT);
    pinMode(stepPinG, OUTPUT);
    pinMode(dirPinG, OUTPUT);
}

char motor_free()
{
    return (r_pas_restantsD <= 0 && r_pas_restantsG <= 0);
}

void motor_step()
{
    if (mot_libreD && mot_libreG)
        delay(DELAY_BY_STEP_WHILE_STOP);
    ver_avancerG();
    ver_avancerD();
    // avancerMotD1(10000, 1);
}

void schedule_standby(unsigned int delta_t)
{
    def_avancerD(0, 0);
    def_avancerG(0, 0);
    r_pas_restantsD = delta_t/DELAY_BY_STEP_WHILE_STOP;
    r_pas_restantsG = r_pas_restantsD;
    mot_libreD = 1;
    mot_libreG = 1;
}

void def_avancerD(unsigned int pas, char dir)
{
    r_pasD = pas;
    // r_dirD = dir;
    r_timeD = micros();
    r_delaiD = vit_min;
    r_pas_faitsD = 0;
    r_pas_restantsD = pas;
    mot_libreD = 0;
    if (dir > 0)
        digitalWrite(dirPinD, LOW);
    if (dir <= 0)
        digitalWrite(dirPinD, HIGH);
}

void def_avancerG(unsigned int pas, char dir)
{
    r_pasG = pas;
    // r_dirG = dir;
    r_timeG = micros();
    r_delaiG = vit_min;
    r_pas_faitsG = 0;
    r_pas_restantsG = pas;
    mot_libreG = 0;
    if (dir > 0)
        digitalWrite(dirPinG, HIGH);
    if (dir <= 0)
        digitalWrite(dirPinG, LOW);
}

void ver_avancerD()
{
    if (mot_libreD) {
        if (r_pas_restantsD <= 0)
            mot_libreD = 0;
        else
            r_pas_restantsD--;
    } else {
        if (micros() - r_timeD >= r_delaiD)
        {
            r_timeD = micros();
            if (r_hlD == 0)
            {
                digitalWrite(stepPinD, HIGH);
                r_hlD = 1;
            }
            else
            {
                digitalWrite(stepPinD, LOW);
                r_hlD = 0;
                r_pas_restantsD--;
                r_pas_faitsD++;
                if (r_delaiD > vit_max && r_pas_faitsD <= r_pasD / 2)
                {
                    r_delaiD -= vit_rampe;
                }
                if (r_pas_restantsD < (vit_min - vit_max) / vit_rampe || (r_pasD < 2 * (vit_min - vit_max) / vit_rampe && r_pas_restantsD < r_pasD / 2))
                {
                    r_delaiD += vit_rampe;
                }
            }
        }
    }
}

void ver_avancerG()
{
    if (mot_libreG) {
        if (r_pas_restantsG <= 0)
            mot_libreG = 0;
        else
            r_pas_restantsG--;
    } else {
        if (micros() - r_timeG >= r_delaiG)
        {
            r_timeG = micros();
            if (r_hlG == 0)
            {
                digitalWrite(stepPinG, HIGH);
                r_hlG = 1;
            }
            else
            {
                digitalWrite(stepPinG, LOW);
                r_hlG = 0;
                r_pas_restantsG--;
                r_pas_faitsG++;
                if (r_delaiG > vit_max && r_pas_faitsG <= r_pasG / 2)
                {
                    r_delaiG -= vit_rampe;
                }
                if (r_pas_restantsG < (vit_min - vit_max) / vit_rampe || (r_pasG < 2 * (vit_min - vit_max) / vit_rampe && r_pas_restantsG < r_pasG / 2))
                {
                    r_delaiG += vit_rampe;
                }
            }
        }
    }
}

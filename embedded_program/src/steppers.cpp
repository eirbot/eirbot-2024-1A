#include "SPI.h"
#include "XNucleoIHM02A1.h"
#include "L6470.h"
#include "steppers.h"
#include "pins.h"
#include "Servo.h"

/* Definitions ---------------------------------------------------------------*/

/* Number of movements per revolution. */
#define MPR_1 4

/* Number of steps. */
#define STEPS_1 (200 * 128)   /* 1 revolution given a 400 steps motor configured at 1/128 microstep mode. */
#define STEPS_2 (STEPS_1 * 2)

/* Delay in milliseconds. */
#define DELAY_1 1000
#define DELAY_2 2000
#define DELAY_3 5000

#define SPEED 300

#define SerialPort Serial

/* Variables -----------------------------------------------------------------*/

/* Motor Control Expansion Board. */
XNucleoIHM02A1 *x_nucleo_ihm02a1;
SPIClass *dev_spi;
L6470 **motors;
int loops = 0;

/* Initialization parameters of the motors connected to the expansion board. */
L6470_init_t L6470_init[L6470DAISYCHAINSIZE] = {
    /* First Motor. */
    {
        9.0,                           /* Motor supply voltage in V. */
        200,                           /* Min number of steps per revolution for the motor. */
        1.9,                           /* Max motor phase voltage in A. */
        3.75,                          /* Max motor phase voltage in V. */
        150.0,                         /* Motor initial speed [step/s]. */
        600.0,                         /* Motor acceleration [step/s^2] (comment for infinite acceleration mode). */
        600.0,                         /* Motor deceleration [step/s^2] (comment for infinite deceleration mode). */
        300.0,                         /* Motor maximum speed [step/s]. */
        0.0,                           /* Motor minimum speed [step/s]. */
        602.7,                         /* Motor full-step speed threshold [step/s]. */
        3.06,                          /* Holding kval [V]. */
        3.06,                          /* Constant speed kval [V]. */
        3.06,                          /* Acceleration starting kval [V]. */
        3.06,                          /* Deceleration starting kval [V]. */
        61.52,                         /* Intersect speed for bemf compensation curve slope changing [step/s]. */
        392.1569e-6,                   /* Start slope [s/step]. */
        643.1372e-6,                   /* Acceleration final slope [s/step]. */
        643.1372e-6,                   /* Deceleration final slope [s/step]. */
        0,                             /* Thermal compensation factor (range [0, 15]). */
        3.06 * 1000 * 1.10,            /* Ocd threshold [ma] (range [375 ma, 6000 ma]). */
        3.06 * 1000 * 1.00,            /* Stall threshold [ma] (range [31.25 ma, 4000 ma]). */
        StepperMotor::STEP_MODE_1_128, /* Step mode selection. */
        0xFF,                          /* Alarm conditions enable. */
        0x2E88                         /* Ic configuration. */
    },

    /* Second Motor. */
    {
        9.0,                           /* Motor supply voltage in V. */
        200,                           /* Min number of steps per revolution for the motor. */
        1.9,                           /* Max motor phase voltage in A. */
        3.75,                          /* Max motor phase voltage in V. */
        150.0,                         /* Motor initial speed [step/s]. */
        600.0,                         /* Motor acceleration [step/s^2] (comment for infinite acceleration mode). */
        600.0,                         /* Motor deceleration [step/s^2] (comment for infinite deceleration mode). */
        300.0,                         /* Motor maximum speed [step/s]. */
        0.0,                           /* Motor minimum speed [step/s]. */
        602.7,                         /* Motor full-step speed threshold [step/s]. */
        3.06,                          /* Holding kval [V]. */
        3.06,                          /* Constant speed kval [V]. */
        3.06,                          /* Acceleration starting kval [V]. */
        3.06,                          /* Deceleration starting kval [V]. */
        61.52,                         /* Intersect speed for bemf compensation curve slope changing [step/s]. */
        392.1569e-6,                   /* Start slope [s/step]. */
        643.1372e-6,                   /* Acceleration final slope [s/step]. */
        643.1372e-6,                   /* Deceleration final slope [s/step]. */
        0,                             /* Thermal compensation factor (range [0, 15]). */
        3.06 * 1000 * 1.10,            /* Ocd threshold [ma] (range [375 ma, 6000 ma]). */
        3.06 * 1000 * 1.00,            /* Stall threshold [ma] (range [31.25 ma, 4000 ma]). */
        StepperMotor::STEP_MODE_1_128, /* Step mode selection. */
        0xFF,                          /* Alarm conditions enable. */
        0x2E88                         /* Ic configuration. */
    }
};

Servo servo; // création de l'objet "servo"

void board_setup()
{
    /*----- Initialization. -----*/

    /* Initializing SPI bus. */
    dev_spi = new SPIClass(D11, D12, D3);

    /* Initializing Motor Control Expansion Board. */
    x_nucleo_ihm02a1 = new XNucleoIHM02A1(&L6470_init[0], &L6470_init[1], A4, A5, D4, A2, dev_spi);

    /* Building a list of motor control components. */
    motors = x_nucleo_ihm02a1->get_components();

    servo.attach(servoPin);
    servo.write(90);
}

void setServo(char angle){
    servo.write(angle); // demande au servo de se déplacer à cette position
    // for (int i=0; i<)
}

void avancer(unsigned int pas){
    motors[1]->move(StepperMotor::BWD, pas);
    delay(24);
    motors[0]->move(StepperMotor::BWD, pas);

    // x_nucleo_ihm02a1->perform_prepared_actions();
}

void avancerVit(){
    motors[1]->prepare_run(StepperMotor::BWD, SPEED);
    motors[0]->prepare_run(StepperMotor::BWD, SPEED);

    x_nucleo_ihm02a1->perform_prepared_actions();
}

void reculer(unsigned int pas){
    motors[1]->move(StepperMotor::FWD, pas);
    delay(21);
    motors[0]->move(StepperMotor::FWD, pas);

    // x_nucleo_ihm02a1->perform_prepared_actions();
}

void reculerVit(){
    motors[1]->prepare_run(StepperMotor::FWD, SPEED);
    motors[0]->prepare_run(StepperMotor::FWD, SPEED);

    x_nucleo_ihm02a1->perform_prepared_actions();
}

void tournerDroite(int pasG, int pasD){

    motors[1]->prepare_move(StepperMotor::FWD, pasG);
    motors[0]->prepare_move(StepperMotor::BWD, pasD);

    x_nucleo_ihm02a1->perform_prepared_actions();
}

void tournerDroiteVit(){

    motors[1]->prepare_run(StepperMotor::FWD, SPEED);
    motors[0]->prepare_run(StepperMotor::BWD, SPEED);

    x_nucleo_ihm02a1->perform_prepared_actions();
}

void tournerGauche(int pasG, int pasD){

    motors[1]->prepare_move(StepperMotor::BWD, pasG);
    motors[0]->prepare_move(StepperMotor::FWD, pasD);

    x_nucleo_ihm02a1->perform_prepared_actions();
}

void tournerGaucheVit(){

    motors[1]->prepare_run(StepperMotor::BWD, SPEED);
    motors[0]->prepare_run(StepperMotor::FWD, SPEED);

    x_nucleo_ihm02a1->perform_prepared_actions();
}

void hardStop(){
    motors[0]->prepare_hard_stop();
    motors[1]->prepare_hard_stop();

    x_nucleo_ihm02a1->perform_prepared_actions();
}

void setSpeed(int stepPerSec){
    if(stepPerSec >= 0){
        motors[0]->prepare_run(StepperMotor::BWD, stepPerSec);
        motors[1]->prepare_run(StepperMotor::BWD, stepPerSec);
    }
    else{
        motors[0]->prepare_run(StepperMotor::FWD, -stepPerSec);
        motors[1]->prepare_run(StepperMotor::FWD, -stepPerSec);
    }

    x_nucleo_ihm02a1->perform_prepared_actions();
}

char motor_free(){
    return !(motors[0]->is_active() || motors[1]->is_active());
}

int motorPos(enum motor motor){
    return motors[motor]->get_position();
}

void motorSetHome(enum motor motor){
    motors[motor]->set_home();
}

int motorSpeed(enum motor motor){
    return motors[motor]->get_speed();
}

int motorPar(enum motor motor){
    return motors[motor]->get_parameter(L6470_CONFIG_ID);
}




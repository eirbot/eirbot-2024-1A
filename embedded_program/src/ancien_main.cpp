/**
 ******************************************************************************
 * @file    X_NUCLEO_IHM02A1_HelloWorld.ino
 * @author  STMicroelectronics
 * @version V1.0.0
 * @date    11 October 2017
 * @brief   Arduino test application for the STMicroelectronics X-NUCLEO-IHM02A1
 *          Motor Control Expansion Board: control of 2 motors.
 ******************************************************************************
 * @attention
 *
 * <h2><center>&copy; COPYRIGHT(c) 2017 STMicroelectronics</center></h2>
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *   1. Redistributions of source code must retain the above copyright notice,
 *      this list of conditions and the following disclaimer.
 *   2. Redistributions in binary form must reproduce the above copyright notice,
 *      this list of conditions and the following disclaimer in the documentation
 *      and/or other materials provided with the distribution.
 *   3. Neither the name of STMicroelectronics nor the names of its contributors
 *      may be used to endorse or promote products derived from this software
 *      without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 ******************************************************************************
 */


/* Includes ------------------------------------------------------------------*/

/* Arduino specific header files. */
#include "Arduino.h"

/* Helper header files. */
#include "SPI.h"

/* Expansion Board specific header files. */
#include "XNucleoIHM02A1.h"


/* Definitions ---------------------------------------------------------------*/

/* Number of movements per revolution. */
#define MPR_1 4

/* Number of steps. */
#define STEPS_1 (400 * 128)   /* 1 revolution given a 400 steps motor configured at 1/128 microstep mode. */
#define STEPS_2 (STEPS_1 * 2)

/* Delay in milliseconds. */
#define DELAY_1 1000
#define DELAY_2 2000
#define DELAY_3 5000

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
        12.0,                           /* Motor supply voltage in V. */
        200,                           /* Min number of steps per revolution for the motor. */
        1.5,                           /* Max motor phase voltage in A. */
        3.75,                          /* Max motor phase voltage in V. */
        100.0,                         /* Motor initial speed [step/s]. */
        70.0,                         /* Motor acceleration [step/s^2] (comment for infinite acceleration mode). */
        70.0,                         /* Motor deceleration [step/s^2] (comment for infinite deceleration mode). */
        100.0,                         /* Motor maximum speed [step/s]. */
        0.0,                           /* Motor minimum speed [step/s]. */
        100.7,                         /* Motor full-step speed threshold [step/s]. */
        3.06,                          /* Holding kval [V]. */
        3.06,                          /* Constant speed kval [V]. */
        3.06,                          /* Acceleration starting kval [V]. */
        3.06,                          /* Deceleration starting kval [V]. */
        61.52,                         /* Intersect speed for bemf compensation curve slope changing [step/s]. */
        392.1569e-4,                   /* Start slope [s/step]. */
        643.1372e-4,                   /* Acceleration final slope [s/step]. */
        643.1372e-4,                   /* Deceleration final slope [s/step]. */
        0,                             /* Thermal compensation factor (range [0, 15]). */
        3.06 * 1000 * 1.10,            /* Ocd threshold [ma] (range [375 ma, 6000 ma]). */
        3.06 * 1000 * 1.00,            /* Stall threshold [ma] (range [31.25 ma, 4000 ma]). */
        StepperMotor::STEP_MODE_1_128, /* Step mode selection. */
        0xFF,                          /* Alarm conditions enable. */
        0x2E88                         /* Ic configuration. */
    },

    /* Second Motor. */
    {
        12.0,                           /* Motor supply voltage in V. */
        200,                           /* Min number of steps per revolution for the motor. */
        1.5,                           /* Max motor phase voltage in A. */
        3.75,                          /* Max motor phase voltage in V. */
        300.0,                         /* Motor initial speed [step/s]. */
        70.0,                         /* Motor acceleration [step/s^2] (comment for infinite acceleration mode). */
        70.0,                         /* Motor deceleration [step/s^2] (comment for infinite deceleration mode). */
        992.0,                         /* Motor maximum speed [step/s]. */
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

void demo1(){
    motors[0]->prepare_run(StepperMotor::FWD, 442);
    motors[1]->prepare_run(StepperMotor::FWD, 442);

    x_nucleo_ihm02a1->perform_prepared_actions();

    motors[0]->wait_while_active();
    motors[1]->wait_while_active();

    delay(2000);

    motors[0]->prepare_run(StepperMotor::FWD, 442);
    motors[1]->prepare_run(StepperMotor::FWD, 243);

    x_nucleo_ihm02a1->perform_prepared_actions();

    motors[0]->wait_while_active();
    motors[1]->wait_while_active();

    delay(5654);

    motors[0]->prepare_run(StepperMotor::FWD, 243);
    motors[1]->prepare_run(StepperMotor::FWD, 442);

    x_nucleo_ihm02a1->perform_prepared_actions();

    motors[0]->wait_while_active();
    motors[1]->wait_while_active();

    delay(5654);

    motors[0]->prepare_run(StepperMotor::BWD, 243);
    motors[1]->prepare_run(StepperMotor::BWD, 442);

    x_nucleo_ihm02a1->perform_prepared_actions();

    motors[0]->wait_while_active();
    motors[1]->wait_while_active();

    delay(5654);

    motors[0]->prepare_run(StepperMotor::BWD, 442);
    motors[1]->prepare_run(StepperMotor::BWD, 243);

    x_nucleo_ihm02a1->perform_prepared_actions();

    motors[0]->wait_while_active();
    motors[1]->wait_while_active();

    delay(5654);

    motors[0]->prepare_run(StepperMotor::BWD, 442);
    motors[1]->prepare_run(StepperMotor::BWD, 442);

    x_nucleo_ihm02a1->perform_prepared_actions();

    motors[0]->wait_while_active();
    motors[1]->wait_while_active();

    delay(3000);
}

void demo2(){
    motors[0]->prepare_run(StepperMotor::FWD, 400);
    motors[1]->prepare_run(StepperMotor::FWD, 400);

    x_nucleo_ihm02a1->perform_prepared_actions();

    motors[0]->wait_while_active();
    motors[1]->wait_while_active();

    delay(1000);

    motors[0]->prepare_run(StepperMotor::FWD, 0);
    motors[1]->prepare_run(StepperMotor::FWD, 0);

    x_nucleo_ihm02a1->perform_prepared_actions();

    motors[0]->wait_while_active();
    motors[1]->wait_while_active();

    delay(1000);

    // motors[0]->prepare_move(StepperMotor::BWD, 200*128);
    // motors[1]->prepare_move(StepperMotor::BWD, 200*128);

    // x_nucleo_ihm02a1->perform_prepared_actions();

    // motors[0]->wait_while_active();
    // motors[1]->wait_while_active();

    // delay(1000);
    // motors[0]->prepare_move(StepperMotor::FWD, 200*128);
    // motors[1]->prepare_move(StepperMotor::FWD, 200*128);

    // x_nucleo_ihm02a1->perform_prepared_actions();

    // motors[0]->wait_while_active();
    // motors[1]->wait_while_active();

    // delay(1000);
}

void demo3(){
    motors[0]->prepare_move(StepperMotor::FWD, 884*128);
    motors[1]->prepare_move(StepperMotor::FWD, 884*128);

    x_nucleo_ihm02a1->perform_prepared_actions();

    motors[0]->wait_while_active();
    motors[1]->wait_while_active();

    // motors[0]->prepare_move(StepperMotor::FWD, 1125*128);

    // x_nucleo_ihm02a1->perform_prepared_actions();

    // motors[0]->wait_while_active();
    // motors[1]->wait_while_active();

    // motors[1]->prepare_move(StepperMotor::FWD, 1125*128);

    // x_nucleo_ihm02a1->perform_prepared_actions();

    // motors[0]->wait_while_active();
    // motors[1]->wait_while_active();

    // delay(1000);
    motors[1]->move(StepperMotor::FWD, 884*128);
}


/* setup ----------------------------------------------------------------------*/

void setup()
{
    /*----- Initialization. -----*/

    /* Please verify your board has these spi pins */
    /* Initializing SPI bus. */
    dev_spi = new SPIClass(D11, D12, D3);
    SerialPort.begin(115200);

    /* Initializing Motor Control Expansion Board. */
    x_nucleo_ihm02a1 = new XNucleoIHM02A1(&L6470_init[0], &L6470_init[1], A4, A5, D4, A2, dev_spi);

    /* Building a list of motor control components. */
    motors = x_nucleo_ihm02a1->get_components();

    L6470_init[1].step_sel = StepperMotor::STEP_MODE_1_128;
}

/* loop ----------------------------------------------------------------------*/

void loop()
{
    demo2();
    loops++;
    Serial.println(loops);
}



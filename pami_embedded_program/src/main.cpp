#include <Arduino.h>
#include "TickTwo.h"
#include "motor.h"
#include "captor.h"

const int Pin1m1 = 5;                       const int Pin1m2 = 19; 
const int Pin2m1 = 18;                      const int Pin2m2 = 21;
const int Pin3m1 = 2;                       const int Pin3m2 = 4;

const int Pin1c1 =27;                          const int Pin1c2 =24;
const int Pin2c1 =26;                          const int Pin2c2 =33;


int k = 0;

Motor MotorL(Pin1m1, Pin2m1, Pin3m1);       
Motor MotorR(Pin1m2, Pin2m2, Pin3m2); 

Captor CaptorL(Pin1c1,Pin2c1);
Captor CaptorR(Pin1c2,Pin2c2);


uint32_t topsCount_LA = 0;
bool topsValue_LB;
uint32_t topsCount_RA = 0;
bool topsValue_RB;

uint32_t  intervalTemp = 100; //ms
uint32_t  Time_Trapeze = 0;
uint32_t  Time_Timer = 0;
uint32_t  OmegaMotor = 200; //deg/s
uint32_t  SpeedL;
uint32_t  SpeedR;



struct flags {
  bool avancer;
  bool sens;
  bool Running;
  bool enable_ticker;
};
typedef struct flags flags;

flags flag;


int Trampe = 1000;
int Tplat = 2000;
int MaxValue = 200;
int Value;

void trapeze_fonction ();
void timer_fonction();
void motor_fonction();
void strat_fonction();
void sensor_fonction();
void countTopsL();
void countTopsR();


TickTwo ticker  (trapeze_fonction, intervalTemp, 0, MILLIS);
TickTwo motor   (motor_fonction, intervalTemp,0 , MILLIS);
TickTwo strat   (strat_fonction, intervalTemp, 0, MILLIS);
TickTwo sensor  (sensor_fonction, intervalTemp, 0, MILLIS);
TickTwo timer (timer_fonction, intervalTemp/100, 0, MILLIS);

void setup() {

  pinMode(Pin1m1, OUTPUT);
  pinMode(Pin2m1, OUTPUT);
  pinMode(Pin3m1, OUTPUT);
  attachInterrupt(digitalPinToInterrupt(Pin1c1), countTopsL, RISING);
  //attachInterrupt(digitalPinToInterrupt(Pin1c2), countTopsR, RISING);
  flag.Running = false;
  flag.avancer = true;
  flag.sens = true;
  flag.enable_ticker = true;
  Serial.begin(9600);
  motor.start();
  strat.start();
  timer.start();
  sensor.start();
}

void loop() {
  ticker.update();
  motor.update();
  strat.update();
  timer.update();
  sensor.update();
  Serial.printf("%d SpeedL , %d SpeedR, %d time \n", SpeedL, SpeedR, Time_Timer);
  //Serial.printf("%d value ", Value);
  //Serial.printf("%d Running ", flag.Running);
  //Serial.printf("%d time_trapeze \n", Time_Trapeze);
  //Serial.printf("%d speedleft     ", SpeedreadL);
  //Serial.printf("%d speedright \n", SpeedreadR);

}


void trapeze_fonction()
{
  if (flag.enable_ticker && Time_Trapeze <= 2 * Trampe + Tplat)
  { 
    
    if (Time_Trapeze<Trampe)
    {
      Value = MaxValue * Time_Trapeze
    /Trampe;
    }
    else if (Time_Trapeze<Trampe+Tplat)
    {
      Value = MaxValue;
    }
    else if (Time_Trapeze<= 2 * Trampe + Tplat)
    {
      Value = MaxValue - MaxValue * (Time_Trapeze-Tplat-Trampe)/Trampe;
    } 
    Time_Trapeze = intervalTemp*ticker.counter();
    flag.Running = true;
  }
  else
  {
    flag.Running = false;
    Value = 0;
    Time_Trapeze = 0;
    ticker.stop();
  }
}

void motor_fonction()
{
  if (flag.enable_ticker)
  {
    if (flag.avancer)
    {
      
        MotorL.setPwm(Value, flag.sens);
        MotorR.setPwm(Value, flag.sens);
    }
  }
  else
  {
      MotorL.setPwm(Value, not flag.sens);
      MotorR.setPwm(Value, flag.sens);
    }
}

void strat_fonction(){

  if (not flag.Running && k == 0)
  {
      flag.avancer =  true;
      flag.sens = false;
      ticker.start();
      k = 1;

  } 
  else if (not flag.Running && k == 1)
  {
      flag.avancer =  true;
      flag.sens = true;
      ticker.start();
      k = 0;
  }
  
}

void sensor_fonction(){
  if (Time_Timer> 10){
    SpeedL = topsCount_LA/Time_Timer;
    SpeedR = topsCount_RA/Time_Timer;
    if (topsValue_LB){
      SpeedL = -1*SpeedL;
    }
    if (topsValue_RB){
      SpeedR = -1*SpeedR;
    }
    Time_Timer = 0;
    topsCount_LA = 0;
    topsCount_RA = 0;
  }
}

void countTopsL() {
  topsCount_LA ++;
  topsValue_LB = digitalRead(Pin2c1);
}

void countTopsR() {
  topsCount_RA ++;
  topsValue_RB = digitalRead(Pin2c2);
}

void timer_fonction(){
  Time_Timer++;
}
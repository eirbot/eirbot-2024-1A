#include <Arduino.h>
#include "TickTwo.h"

const int PinEnableMg   = 5;                   
const int PinIn1Mg      = 19; 
const int PinIn2Mg      = 18; 

uint32_t  intervalTemp  = 100; //ms
uint32_t  Time_Trapeze  = 0;
uint32_t  Time_Timer    = 0;
uint32_t  OmegaMotor    = 200; //deg/s

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
void motor_fonction();
void strat_fonction();

TickTwo ticker  (trapeze_fonction, intervalTemp, 0, MILLIS);
TickTwo motor   (motor_fonction, intervalTemp,0 , MILLIS);
TickTwo strat   (strat_fonction, intervalTemp, 0, MILLIS);

void setup() {

  pinMode(PinEnableMg, OUTPUT);
  pinMode(PinIn1Mg, OUTPUT);
  pinMode(PinIn2Mg, OUTPUT);

    flag.Running = false;
  flag.enable_ticker = true;
  Serial.begin(9600);
  motor.start();
  strat.start();

}

void loop() {
  ticker.update();
  motor.update();
  strat.update();

}

void trapeze_fonction()
{
  if (flag.enable_ticker && Time_Trapeze <= 2 * Trampe + Tplat)
  { 
    
    if (Time_Trapeze<Trampe)
    {
      Value = MaxValue * Time_Trapeze/Trampe;
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
    if (flag.avancer==true)
    {
      if (flag.sens){
        analogWrite(PinEnableMg, Value);
        digitalWrite(PinIn1Mg, HIGH);
        digitalWrite(PinIn2Mg, LOW);
      }
      else{
        analogWrite(PinEnableMg, Value);
        digitalWrite(PinIn1Mg, LOW);
        digitalWrite(PinIn2Mg, HIGH);

      }
    }      
    else if (not flag.avancer)
    {
      if (flag.sens==true){
        analogWrite(PinEnableMg, Value);
        digitalWrite(PinIn1Mg, HIGH);
        digitalWrite(PinIn2Mg, LOW);
      
      }
      else {
        analogWrite(PinEnableMg, Value);
        digitalWrite(PinIn1Mg, LOW);
        digitalWrite(PinIn2Mg, HIGH);

      }
      
    }
  }
}

void strat_fonction(){

  if (not flag.Running)
  {
      flag.avancer = true;
      flag.sens = false;
      ticker.start();
      
  } 
}
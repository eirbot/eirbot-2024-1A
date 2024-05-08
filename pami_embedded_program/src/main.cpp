#include <Arduino.h>
#include "TickTwo.h"
#include "motor.h"
//#include "captor.h"

const int Pin1mg = 5;                       
const int Pin1md = 19; 
const int Pin2mg = 18;                      
const int Pin2md = 21;
const int Pin3mg = 2;                       
const int Pin3md = 4;

const int Pin1c1 =27;                          
const int Pin1c2 =24;
const int Pin2c1 =26;                          
const int Pin2c2 =33;


int e = 0;
int e1 = 0;
int e2 =0;

Motor MotorL(Pin1md, Pin2md, Pin3md);       
Motor MotorR(Pin1mg, Pin2mg, Pin3mg); 

//Captor CaptorL(Pin1c1,Pin2c1);
//Captor CaptorR(Pin1c2,Pin2c2);


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
//void timer_fonction();
void motor_fonction();
void strat_fonction();
//void sensor_fonction_ass();
//void sensor_fonction_utile();
//void countTopsL();
//void countTopsR();


TickTwo ticker  (trapeze_fonction, intervalTemp, 0, MILLIS);
TickTwo motor   (motor_fonction, intervalTemp,0 , MILLIS);
TickTwo strat   (strat_fonction, intervalTemp, 0, MILLIS);
//TickTwo sensor  (sensor_fonction_ass, intervalTemp, 0, MILLIS);
//TickTwo timer (timer_fonction, intervalTemp/100, 0, MILLIS);

void setup() {

  pinMode(Pin1md, OUTPUT);
  pinMode(Pin2md, OUTPUT);
  pinMode(Pin3md, OUTPUT);
  //attachInterrupt(digitalPinToInterrupt(Pin1c1), countTopsL, RISING);
  //attachInterrupt(digitalPinToInterrupt(Pin1c2), countTopsR, RISING);
  flag.Running = false;
  flag.enable_ticker = true;
  Serial.begin(9600);
  motor.start();
  strat.start();
  //timer.start();
  //sensor.start();
}

void loop() {
  ticker.update();
  motor.update();
  strat.update();
  //timer.update();
  //sensor.update();
  //Serial.printf("%d value, %d k\n", Value, k);
  //Serial.printf("%d value ", Value);
  //Serial.printf("%d Running ", flag.Running);
  //Serial.printf("%d time_trapeze \n", Time_Trapeze);
  //Serial.printf("%d speedleft     ", SpeedreadL);
  //Serial.printf("%d speedright \n", SpeedreadR);
  if(e1){Serial.printf("error flag.avancer=true/flag.sens\n");}
  if(e2){Serial.printf("error flag.avancer=false/flag.sens\n");}
  if(e){Serial.printf("error flag.avancer\n");}

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
    if (flag.avancer==true)
    {
      if (flag.sens == true){
        analogWrite(Pin3md, Value);
        digitalWrite(Pin1md, HIGH);
        digitalWrite(Pin2md, LOW);
      
        analogWrite(Pin3mg, Value);
        digitalWrite(Pin1mg, HIGH);
        digitalWrite(Pin2mg, LOW);
      }
      else if (flag.sens==false){
        analogWrite(Pin3md, Value);
        digitalWrite(Pin1md, LOW);
        digitalWrite(Pin2md, HIGH);

        analogWrite(Pin3mg, Value/2);
        digitalWrite(Pin1mg, LOW);
        digitalWrite(Pin2mg, HIGH);
      }
      else{
        e1=1;
      }
    }   
    
    else if (flag.avancer==false)
    {
      if (flag.sens==true){
        analogWrite(Pin3m1, Value);
        digitalWrite(Pin1m1, HIGH);
        digitalWrite(Pin2m1, LOW);
      
        analogWrite(Pin3m2, Value);
        digitalWrite(Pin2m1, LOW);
        digitalWrite(Pin2m2, HIGH);
      }
      else if (flag.sens==false){
        analogWrite(Pin3m1, Value);
        digitalWrite(Pin1m1, LOW);
        digitalWrite(Pin1m2, HIGH);
        
        analogWrite(Pin3m2, Value);
        digitalWrite(Pin2m1, HIGH);
        digitalWrite(Pin2m2, LOW);
      }
      else{
        e2=1;
      }
    }
    else{
      e=1;
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
  // else if (not flag.Running && k == 1)
  // {
  //     flag.avancer =  true;
  //     flag.sens = true;
  //     ticker.start();
  //     k = 0;
  // }
  
}

// void sensor_fonction_ass(){
//   if (Time_Timer> 10){
//     SpeedL = topsCount_LA/Time_Timer;
//     SpeedR = topsCount_RA/Time_Timer;
//     if (topsValue_LB){
//       SpeedL = -1*SpeedL;
//     }
//     if (topsValue_RB){
//       SpeedR = -1*SpeedR;
//     }
//     Time_Timer = 0;
//     topsCount_LA = 0;
//     topsCount_RA = 0;
//   }
//}

// void sensor_fonction_utile(){
//   if (not flag.Running){
//     topsCount_LA = 0;
//   }

// }

// void countTopsL() {
//   topsCount_LA ++;
//   topsValue_LB = digitalRead(Pin2c1);
// }

// void countTopsR() {
//   topsCount_RA ++;
//   topsValue_RB = digitalRead(Pin2c2);
// }

// void timer_fonction(){
//   Time_Timer++;
// }
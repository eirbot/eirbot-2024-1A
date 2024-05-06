#include <Arduino.h>
extern "C++" {
  #include "printing.h"
}

void printingStr(const char *msg) {
  Serial.println(msg);
}

void printingInt(const int msg){
  Serial.println(msg);
}

void printingFloat(const float msg){
  Serial.println(msg);
}
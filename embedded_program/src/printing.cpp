#include <Arduino.h>
extern "C++" {
  #include "printing.h"
}

void printing(const char *msg) {
  Serial.println(msg);
}

void printing(const int msg){
  Serial.println(msg);
}

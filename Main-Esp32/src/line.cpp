#include "line.hpp"

void beginLine(){
  pinMode(PIN_A, INPUT);
  pinMode(PIN_B, INPUT);
  pinMode(PIN_C, INPUT);
}

LineResult readLine(){
  LineResult result;
  result.a = digitalRead(PIN_A);
  result.b = digitalRead(PIN_B);
  result.c = digitalRead(PIN_C);
  return result;
}
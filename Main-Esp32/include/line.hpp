#include <Arduino.h>

#pragma once

#define PIN_A 36
#define PIN_B 37
#define PIN_C 38

struct LineResult
{
  bool a;
  bool b;
  bool c;
};

void beginLine();

LineResult readLine();

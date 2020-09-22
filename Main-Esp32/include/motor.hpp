#include <Arduino.h>
#include <Wire.h>

#pragma once

#define MOTOR_CONTROLER 0x08

enum Motors {
  BackLeft = 0,
  BackRight = 1,
  FrontRight = 2,
  FrontLeft = 3
};

void moveMotor(Motors motor, uint8_t speed, bool dir);
void moveMotor(Motors motor, int16_t speed);

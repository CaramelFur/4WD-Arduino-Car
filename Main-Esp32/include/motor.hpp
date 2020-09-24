#include <Arduino.h>
#include <Wire.h>

#pragma once

#define MOTOR_CONTROLER_I2C_ADRESS 0x08

//#define MPS_VALUE_A (float)0.0037768
//#define MPS_VALUE_B (float)0.43835
#define MPS_VALUE_A (float)0.0023
#define MPS_VALUE_B (float)0.725

enum Motors {
  BackLeft = 0,
  BackRight = 1,
  FrontRight = 2,
  FrontLeft = 3
};

void moveMotor(Motors motor, uint8_t speed, bool dir);
void moveMotor(Motors motor, int16_t speed);
void moveAllMotors(int16_t speed);
void moveAllMotors(uint8_t speed, bool dir);

int speedToPWM(float speed);
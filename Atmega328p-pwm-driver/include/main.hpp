#include <Arduino.h>
#include <SoftPWM.h>
#include <Wire.h>

#pragma once

#define I2C_ADRESS 0x08

void receiveEvent(int input);
void resetPWM();
void readEvent();
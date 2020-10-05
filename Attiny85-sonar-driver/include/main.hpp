#include <Arduino.h>
#include <Wire.h>
#include "Servo.h"

#pragma once

#define I2C_ADRESS 9

#define servoPin 1

#define pingPin 3
#define echoPin 4

#define SONIC_TIMEOUT (maxDistance * 60)

uint16_t getSonar();

void receiveEvent(int howMany);
void readEvent();
void sendInt16(int16_t value);

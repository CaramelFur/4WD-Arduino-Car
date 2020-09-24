#include "Arduino.h"
#include "Wire.h"

#pragma once

#define SENSOR_I2C_ADRESS 0x09

#define SENSOR_CMD_PINGSPEED 0x01
#define SENSOR_CMD_MAXDISTANCE 0x02
#define SENSOR_CMD_SERVOPOS 0x03

#define SENSOR_CMD_RESET 0xf0
#define SENSOR_CMD_FAKEDISTANCE 0xff

struct PullData
{
  uint16_t currentDistance;
  uint16_t fetchSpeed;
  uint16_t maxDistance;
  uint16_t servoPosition;
};

void moveServo(uint8_t position);
void setSonarPingSpeed(uint16_t milliseconds);
void setSonarMaxDistance(uint16_t maxDistance);

void resetServoSensor();

PullData retrieveSensorData();

uint16_t getSonarDistance();
uint16_t getSonarFetchSpeed();
uint16_t getSonarMaxDistance();
uint16_t getServoPosition();

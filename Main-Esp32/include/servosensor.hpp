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
  uint8_t id;
  int16_t currentDistance;
  int16_t fetchSpeed;
  int16_t maxDistance;
  int16_t servoPosition;
};

void moveServo(uint8_t position);
void setSonarPingSpeed(int16_t milliseconds);
void setSonarMaxDistance(int16_t maxDistance);

bool beginServoSensor();
void resetServoSensor();

PullData retrieveSensorData();

int16_t getSonarDistance();
int16_t getSonarFetchSpeed();
int16_t getSonarMaxDistance();
int16_t getServoPosition();

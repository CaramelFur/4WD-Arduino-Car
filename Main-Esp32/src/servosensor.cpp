#include "servosensor.hpp"

void sendU16(uint16_t value)
{
  // Gives narrowing warning, thats ok
  uint8_t send[2] = {
      value >> 8,
      value};
  Wire.write(send, 2);
}

uint16_t readU16()
{
  return (Wire.read() << 8) | Wire.read();
}

void sendCommand(uint8_t command, uint16_t value)
{
  Wire.beginTransmission(SENSOR_I2C_ADRESS);
  Wire.write(command);
  sendU16(value);
  Wire.endTransmission();
}

void moveServo(uint8_t position)
{
  sendCommand(SENSOR_CMD_SERVOPOS, position);
}

void resetServoSensor()
{
  sendCommand(SENSOR_CMD_RESET, 0);
}

void setSonarPingSpeed(uint16_t milliseconds)
{
  sendCommand(SENSOR_CMD_PINGSPEED, milliseconds);
}

void setSonarMaxDistance(uint16_t maxDistance)
{
  sendCommand(SENSOR_CMD_PINGSPEED, maxDistance);
}

PullData retrieveSensorData()
{
  PullData value;

  Wire.requestFrom(SENSOR_I2C_ADRESS, 8);
  while (Wire.available() < 8)
    ;

  value.currentDistance = readU16();
  value.fetchSpeed = readU16();
  value.maxDistance = readU16();
  value.servoPosition = readU16();

  return value;
}

uint16_t getSonarDistance()
{
  return retrieveSensorData().currentDistance;
}

uint16_t getSonarFetchSpeed()
{
  return retrieveSensorData().fetchSpeed;
}

uint16_t getSonarMaxDistance()
{
  return retrieveSensorData().maxDistance;
}

uint16_t getServoPosition()
{
  return retrieveSensorData().servoPosition;
}

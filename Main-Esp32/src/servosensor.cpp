#include "servosensor.hpp"

void send16(uint16_t value)
{
  // Gives narrowing warning, thats ok
  uint8_t send[2] = {
      value >> 8,
      value};
  Wire.write(send, 2);
}

int16_t read16()
{
  return (Wire.read() << 8) | Wire.read();
}

void sendCommand(uint8_t command, int16_t value)
{
  Wire.beginTransmission(SENSOR_I2C_ADRESS);
  Wire.write(command);
  send16(value);
  Wire.endTransmission();
}

bool beginServoSensor()
{
  if (retrieveSensorData().id != SENSOR_I2C_ADRESS)
    return false;
  resetServoSensor();
  return true;
}

void resetServoSensor()
{
  sendCommand(SENSOR_CMD_RESET, 0);
}

void moveServo(uint8_t position)
{
  sendCommand(SENSOR_CMD_SERVOPOS, position);
}

void setSonarPingSpeed(int16_t milliseconds)
{
  sendCommand(SENSOR_CMD_PINGSPEED, milliseconds);
}

void setSonarMaxDistance(int16_t maxDistance)
{
  sendCommand(SENSOR_CMD_PINGSPEED, maxDistance);
}

PullData retrieveSensorData()
{
  PullData value{
      0,
      0,
      -1,
      100,
      90};

  if (Wire.requestFrom(SENSOR_I2C_ADRESS, 9) < 9)
    return value;

  value.id = Wire.read();
  value.currentDistance = read16();
  value.fetchSpeed = read16();
  value.maxDistance = read16();
  value.servoPosition = read16();

  return value;
}

int16_t getSonarDistance()
{
  return retrieveSensorData().currentDistance;
}

int16_t getSonarFetchSpeed()
{
  return retrieveSensorData().fetchSpeed;
}

int16_t getSonarMaxDistance()
{
  return retrieveSensorData().maxDistance;
}

int16_t getServoPosition()
{
  return retrieveSensorData().servoPosition;
}

#include "motor.hpp"

const uint8_t motorPins[4][2] = {
    {1, 0},
    {2, 3},
    {5, 4},
    {6, 7}};

void moveMotor(Motors motor, uint8_t speed, bool dir)
{
  Wire.beginTransmission(MOTOR_CONTROLER_I2C_ADRESS);

  Wire.write(motorPins[motor][dir]);
  Wire.write(0);
  Wire.write(motorPins[motor][!dir]);
  Wire.write(speed);

  Wire.endTransmission();
}

void moveMotor(Motors motor, int16_t speed)
{
  if (speed > 255)
    speed = 255;
  if (speed < -255)
    speed = -255;

  if (speed < 0)
  {
    moveMotor(motor, abs(speed), 0);
  }
  else
  {
    moveMotor(motor, abs(speed), 1);
  }
}

void moveAllMotors(int16_t speed)
{
  for (int i = 0; i < 4; i++)
  {
    moveMotor((Motors)i, speed);
  }
}

void moveAllMotors(uint8_t speed, bool dir)
{
  for (int i = 0; i < 4; i++)
  {
    moveMotor((Motors)i, speed, dir);
  }
}

int speedToPWM(float speed)
{
  return (speed - MPS_VALUE_B) / MPS_VALUE_A;
}
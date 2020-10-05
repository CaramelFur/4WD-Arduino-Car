#include "motor.hpp"

const uint8_t motorPins[4][2] = {
    {1, 0},
    {2, 3},
    {5, 4},
    {6, 7}};

bool beginMotor()
{
  if (readId() != MOTOR_CONTROLLER_I2C_ADRESS)
    return false;
  resetMotor();
  moveAllMotors(0);
  return true;
}

void resetMotor()
{
  Wire.beginTransmission(MOTOR_CONTROLLER_I2C_ADRESS);
  Wire.write(MOTOR_CONTROLLER_CMD_RESET);
  Wire.write(0x00);
  Wire.endTransmission();
}

uint8_t readId()
{
  if (Wire.requestFrom(MOTOR_CONTROLLER_I2C_ADRESS, 1) < 1)
    return 0;
  return Wire.read();
}

void moveMotor(Motors motor, uint8_t speed, bool dir)
{
  Wire.beginTransmission(MOTOR_CONTROLLER_I2C_ADRESS);

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

void moveMotors(Sides side, uint8_t speed, bool dir)
{
  switch (side)
  {
  case Sides::Left:
    moveMotor(Motors::BackLeft, speed, dir);
    moveMotor(Motors::FrontLeft, speed, dir);
    break;
  case Sides::Right:
    moveMotor(Motors::BackRight, speed, dir);
    moveMotor(Motors::FrontRight, speed, dir);
    break;
  case Sides::Front:
    moveMotor(Motors::FrontLeft, speed, dir);
    moveMotor(Motors::FrontRight, speed, dir);
    break;
  case Sides::Back:
    moveMotor(Motors::BackRight, speed, dir);
    moveMotor(Motors::BackLeft, speed, dir);
    break;
  }
}

void moveMotors(Sides side, uint16_t speed)
{
  switch (side)
  {
  case Sides::Left:
    moveMotor(Motors::BackLeft, speed);
    moveMotor(Motors::FrontLeft, speed);
    break;
  case Sides::Right:
    moveMotor(Motors::BackRight, speed);
    moveMotor(Motors::FrontRight, speed);
    break;
  case Sides::Front:
    moveMotor(Motors::FrontLeft, speed);
    moveMotor(Motors::FrontRight, speed);
    break;
  case Sides::Back:
    moveMotor(Motors::BackRight, speed);
    moveMotor(Motors::BackLeft, speed);
    break;
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
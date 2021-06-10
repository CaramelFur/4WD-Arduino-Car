#include "robot.hpp"

void setup()
{
  beginRobot();
}

void loop()
{
  setLeds(CRGB::Red);
  waitForButton();
  delay(500);
  setLeds(CRGB::Green);

  moveMotor(FrontRight, -50);
  moveMotor(FrontLeft, 50);
  moveMotor(BackRight, -50);
  moveMotor(BackLeft, 50);

  delay(1000);

  moveAllMotors(0);

  printString("Done!");
}
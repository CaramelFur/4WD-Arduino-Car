#include "robot.hpp"

void setup()
{
  beginRobot();
  setLeds(CRGB::Red);
  waitForButton();
  setLeds(CRGB::Green);
  printString("Driving");

  int16_t distance = getSonarDistance();
  while (distance > 10)
  {
    printString(String(distance));
    moveAllMotors(100);
    distance = getSonarDistance();
  }

  moveAllMotors(0);
}

void loop()
{
}
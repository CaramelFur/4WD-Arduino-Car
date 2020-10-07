#include "robot.hpp"

enum States
{
  towardsWall,
  turning,
  centering,
  done
};

States state = towardsWall;

int aimdistance = 0;

void setup()
{
  beginRobot();
  setLeds(CRGB::Red);
  waitForButton();
  delay(500);
  setLeds(CRGB::Green);
  printString("Driving");
}

void loop()
{
  switch (state)
  {
  case towardsWall:
  {
    int16_t distance = getSonarDistance();
    printString(String(distance));

    if (distance < 20)
    {
      moveAllMotors(-255);
      delay(100);
      moveAllMotors(0);
      state = turning;
    }
    else if (distance < 50)
    {
      moveAllMotors(100);
    }
    else
    {
      moveAllMotors(100);
    }
  }
  break;

  case turning:
  {
    moveServo(0);
    delay(400);
    int16_t rightDistance = getSonarDistance();
    moveServo(180);
    delay(400);
    int16_t leftDistance = getSonarDistance();

    moveServo(90);

    aimdistance = (leftDistance + rightDistance + 5) / 2 - 25 / 2;

    printString(String(leftDistance), String(rightDistance));

    bool dir = rightDistance >= leftDistance;

    moveMotors(Left, dir ? 255 : -255);
    moveMotors(Right, dir ? -255 : 255);
    delay(dir ? 200 : 230);
    moveAllMotors(0);

    delay(200);

    state = centering;
  }
  break;

  case centering:
  {
    int16_t distance = getSonarDistance();
    printString(String(distance));

    if (distance > aimdistance + 5)
    {
      moveAllMotors(50);
    }
    else if (distance < aimdistance - 5)
    {
      moveAllMotors(-50);
    }
    else
    {

      moveAllMotors(0);
      setLeds(CRGB::Blue);
      state = done;
    }
  }
  break;

  default:
    break;
  }

  delay(10);
}
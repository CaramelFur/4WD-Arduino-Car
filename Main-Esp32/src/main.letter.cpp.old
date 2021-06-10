#include "robot.hpp"

#define STEPS 21
#define SPEED 50
#define CORNERSPEED 255

int robotSteps[STEPS][3] = {
    // Draw letter R
    {SPEED, SPEED, 2000},
    {CORNERSPEED, -CORNERSPEED, 230},
    {SPEED, SPEED, 1000},
    {CORNERSPEED, -CORNERSPEED, 230},
    {SPEED, SPEED, 1000},
    {CORNERSPEED, -CORNERSPEED, 230},
    {SPEED, SPEED, 1000},
    {-CORNERSPEED, CORNERSPEED, 280},
    {-CORNERSPEED, CORNERSPEED, 80},
    {SPEED, SPEED, 1600},

    // Move over
    {-CORNERSPEED, CORNERSPEED, 100},
    {SPEED, SPEED, 1000},

    // Draw letter D
    {SPEED, SPEED, 1000},
    {-SPEED, -SPEED, 1000},
    {-CORNERSPEED, CORNERSPEED, 250},
    {SPEED, SPEED, 1000},
    {CORNERSPEED, -CORNERSPEED, 230},
    {SPEED, SPEED, 1000},
    {CORNERSPEED, -CORNERSPEED, 230},
    {SPEED, SPEED, 1000},
    {-SPEED, -SPEED, 2000},
};

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

  for (int i = 0; i < STEPS; i++)
  {
    printString("Driving...", String(i));
    moveMotors(Left, robotSteps[i][0]);
    moveMotors(Right, robotSteps[i][1]);
    delay(robotSteps[i][2]);
    moveAllMotors(0);
    delay(250);
  }

  printString("Done!");
}
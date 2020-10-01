#include "main.hpp"

CRGB leds[NUM_LEDS];
SSD1306Wire display(DISPLAY_ADDRESS, SDA, SCL);

#define MIN_DISTANCE 20
#define MOTOR_SPEED_NORMAL 60
#define MOTOR_SPEED_TURN 100

const CRGB colors[5] = {CRGB::Red, CRGB::Magenta, CRGB::Blue, CRGB::Yellow, CRGB::Green};

// Setup function
void setup()
{
  // Intialize
  Serial.begin(115200);

  // Wait for serial monitor to connect
  delay(500);

  // Intialize every component
  initLeds();
  initDisplay();
  while (!beginServoSensor())
    ;
  while (!beginMotor())
    ;

  // Fetch distance every 2 milliseconds
  setSonarPingSpeed(2);
  // Done initializing
  printString("Ready!");

  setAllLeds(CRGB::Green);

  // Wait for button press to start
  while (digitalRead(BUTTON_PIN))
    ;
}

int currentMeasure = 0;
bool measure()
{
  // Measure a different position everytime this function is called
  currentMeasure = (currentMeasure + 1) % 4;
  switch (currentMeasure)
  {
  case 0:
    moveServo(40);
    break;
  case 1:
  case 3:
    moveServo(90);
    break;
  case 2:
    moveServo(140);
    break;
  }
  delay(100);
  int16_t dis = getSonarDistance();

  printString(String(dis));
  int16_t remaindis = dis % 20;
  setLeds(0, 4, colors[(dis - remaindis) / 20]);
  int16_t lastRemaindis = dis % 5;
  setLeds(5, 6, colors[(remaindis - lastRemaindis) / 5]);
  setLeds(8, 9, colors[lastRemaindis]);

  return dis > MIN_DISTANCE;
}

// Loop function

void loop()
{
  while (measure())
  {
    moveAllMotors(MOTOR_SPEED_NORMAL);
  }

  moveAllMotors(-MOTOR_SPEED_TURN);
  delay(200);

  if (rand() % 2)
  {
    moveMotors(Left, -MOTOR_SPEED_TURN);
    moveMotors(Right, MOTOR_SPEED_TURN);
  }
  else
  {
    moveMotors(Left, MOTOR_SPEED_TURN);
    moveMotors(Right, -MOTOR_SPEED_TURN);
  }
  delay(500);
  moveAllMotors(0);
}

// Other stuff

void printString(String string)
{
  display.clear();
  display.drawString(0, 0, string);
  display.display();
  Serial.println(string);
}

void initDisplay()
{
  pinMode(OLED_RST, OUTPUT);
  digitalWrite(OLED_RST, LOW);
  delay(50);
  digitalWrite(OLED_RST, HIGH);

  display.init();
  display.flipScreenVertically();
  display.setContrast(255);
  display.setBrightness(255);
  display.setFont(ArialMT_Plain_24);
  display.clear();
  display.display();

  printString("Loading...");
}

void initLeds()
{
  FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);
  setAllLeds(CRGB::Black);
}

void setLeds(int start, int end, CRGB color)
{
  for (int i = start; i <= end; i++)
  {
    leds[i] = color;
  }
  FastLED.show();
}

void setAllLeds(CRGB color)
{
  setLeds(0, NUM_LEDS - 1, color);
}
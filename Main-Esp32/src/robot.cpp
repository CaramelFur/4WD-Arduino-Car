#include "robot.hpp"

void initDisplay();
void initLeds();

CRGB leds[NUM_LEDS];
SSD1306Wire display(DISPLAY_ADDRESS, SDA, SCL);

void beginRobot()
{
  delay(500);

  Serial.begin(115200);

  pinMode(BUTTON_PIN, INPUT);
  initLeds();
  initDisplay();
  while (!beginServoSensor())
    ;
  while (!beginMotor())
    ;
  setSonarPingSpeed(10);
  setSonarAverageAmount(2);
  printString("Ready!");
}

// Other stuff

void waitForButton()
{
  while (digitalRead(BUTTON_PIN))
    ;
}

void printString(String string)
{
  display.clear();
  display.drawString(0, 0, string);
  display.display();
  Serial.println(string);
}

void printString(String string, String string2)
{
  display.clear();
  display.drawString(0, 0, string);
  display.drawString(0, 25, string2);
  display.display();
  Serial.println(string);
  Serial.println(string2);
}

void printString(String string, String string2, String string3)
{
  display.clear();
  display.drawString(0, 0, string);
  display.drawString(0, 25, string2);
  display.drawString(0, 50, string3);
  display.display();
  Serial.println(string);
  Serial.println(string2);
  Serial.println(string3);
}

void setLeds(int start, int end, CRGB color)
{
  for (int i = start; i <= end; i++)
  {
    leds[i] = color;
  }
  FastLED.show();
}

void setLeds(CRGB color)
{
  setLeds(0, NUM_LEDS - 1, color);
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
  setLeds(CRGB::Black);
}
#include "main.hpp"

CRGB leds[NUM_LEDS];

SSD1306 display(DISPLAY_ADDRESS, SDA, SCL);

// Setup function
void setup()
{
  Serial.begin(115200);

  initLeds();
  initDisplay();
  while (!beginServoSensor())
    ;
  while (!beginMotor())
    ;

  setSonarPingSpeed(100);

  printString("Ready");
}

// Loop function
void loop()
{
  String send = String("Distance: ");
  send.concat(getSonarDistance());
  printString(send);
  delay(100);
}

void printString(String string)
{
  display.clear();
  display.drawString(0, 0, string);
  display.display();
}

void initDisplay()
{
  pinMode(OLED_RST, OUTPUT);
  digitalWrite(OLED_RST, LOW);
  delay(50);
  digitalWrite(OLED_RST, HIGH);

  display.init();
  display.flipScreenVertically();
}

void initLeds()
{
  FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);
  for (int i = 0; i < NUM_LEDS; i++)
  {
    leds[i] = CRGB::Black;
  }
  FastLED.show();
}
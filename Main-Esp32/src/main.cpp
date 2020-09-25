#include "main.hpp"

CRGB leds[NUM_LEDS];

//U8G2_SSD1306_128X64_ALT0_1_HW_I2C display(U8G2_R0, /* reset=*/OLED_RST, /* clock=*/SCL, /* data=*/SDA);
SSD1306Wire display(DISPLAY_ADDRESS, SDA, SCL);

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

  delay(2000);

  moveMotors(Sides::Front, 255);
  moveMotors(Sides::Back, -255);

  delay(5000);

  moveAllMotors(0);
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
  display.setContrast(255);
  display.clear();
  display.display();

  printString("Loading...");
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
#include "main.hpp"

#define NUM_LEDS 10
#define DATA_PIN 17

CRGB leds[NUM_LEDS];

SSD1306 display(DISPLAY_ADDRESS, SDA, SCL);

void setup()
{
  delay(100);
  Serial.begin(115200);
  delay(500);
  Serial.println("Hello there");
  Serial.println();

  FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);

  for(int i = 0; i < NUM_LEDS; i++){
    leds[i] = CRGB::Red;
  }

  FastLED.show();

  Wire.setClock(10000);

  initDisplay();

  display.drawString(0, 0, "Hello world");
  display.display();

  display.clear();
  display.drawString(0, 0, "FL");
  display.display();

  for (int i = 0; i <= 255; i++)
  {
    moveMotor(Motors::FrontLeft, i);
    moveMotor(Motors::FrontRight, i);
    moveMotor(Motors::BackLeft, i);
    moveMotor(Motors::BackRight, i);
    display.clear();
    display.drawString(0, 0, String(i));
    display.display();
    delay(20000 / 255);
  }

  moveMotor(Motors::FrontLeft, 0);
  moveMotor(Motors::FrontRight, 0);
  moveMotor(Motors::BackLeft, 0);
  moveMotor(Motors::BackRight, 0);
}

void loop()
{

  /*for(int i = 255; i >= -255; i--){
    moveMotor(Motors::FrontLeft, i);
    delay(2500 / 255);
  }
  for(int i = -255; i <= 0; i++){
    moveMotor(Motors::FrontLeft, i);
    delay(2500 / 255);
  }

  display.drawString(0, 0, "FR");
  display.display();

  for(int i = 0; i <= 255; i++){
    moveMotor(Motors::FrontRight, i);
    delay(2500 / 255);
  }
  for(int i = 255; i >= -255; i--){
    moveMotor(Motors::FrontRight, i);
    delay(2500 / 255);
  }
  for(int i = -255; i <= 0; i++){
    moveMotor(Motors::FrontRight, i);
    delay(2500 / 255);
  }*/

  /*display.clear();
  
  moveMotor(Motors::FrontLeft, 255, 1);
  delay(1000);
  moveMotor(Motors::FrontLeft, 0, 1);
  delay(1000);

  display.clear();
  display.drawString(0, 0, "FR");
  display.display();
  moveMotor(Motors::FrontRight, 255, 1);
  delay(1000);
  moveMotor(Motors::FrontRight, 255, 0);
  delay(1000);*/

  /*display.clear();
  display.drawString(0, 0, "BL");
  display.display();
  moveMotor(Motors::BackLeft, 255, 1);
  delay(1000);
  moveMotor(Motors::BackLeft, 0, 1);
  delay(1000);

  display.clear();
  display.drawString(0, 0, "BR");
  display.display();
  moveMotor(Motors::BackRight, 255, 1);
  delay(1000);
  moveMotor(Motors::BackRight, 0, 1);
  delay(1000);*/
}

void initDisplay()
{
  pinMode(OLED_RST, OUTPUT);
  digitalWrite(OLED_RST, LOW); // set GPIO16 low to reset OLED
  delay(50);
  digitalWrite(OLED_RST, HIGH); // while OLED is running, must set GPIO16 in high

  display.init();
  display.flipScreenVertically();
}

#include "main.hpp"

CRGB leds[NUM_LEDS];
SSD1306Wire display(DISPLAY_ADDRESS, SDA, SCL);

BluetoothSerial SerialBT;

// Setup function
void setup()
{
  // Intialize
  Serial.begin(115200);

  // Wait for serial monitor to connect
  delay(500);

  if (!SerialBT.begin("ESP32"))
    Serial.println("An error occurred initializing Bluetooth");
  else
    SerialBT.setTimeout(10);

  initLeds();
  initDisplay();
  beginLine();
  while (!beginServoSensor())
    ;
  while (!beginMotor())
    ;

  setSonarPingSpeed(100);
  // Done initializing
  printString("Ready!");
}

// Loop function
void loop()
{

  auto line = readLine();
  auto toPrint = String(line.a);
  toPrint.concat(" ");
  toPrint.concat(line.b);
  toPrint.concat(" ");
  toPrint.concat(line.c);
  printString(toPrint);

  if(line.a){
    moveMotors(Sides::Left, 50);
  }else{
    moveMotors(Sides::Left, 0);
  }
  delay(1);
  if(line.c){
    moveMotors(Sides::Right, 50);
  }else{
    moveMotors(Sides::Right, 0);
  }
  delay(1);

  /*if (SerialBT.hasClient())
  {
    printString("Connected");
    while (SerialBT.hasClient())
    {
      String command = SerialBT.readStringUntil('\n');
      if (command.length() != 0)
      {
        Serial.println(command);
        processCommand(command);
      }
    }
    printString("Ready!");
    moveAllMotors(0);
  }*/
  //delay(5);
}

void processCommand(String command)
{
  char base = command.charAt(0);

  if (base == 'L')
  {
    int currentLeftSpeed = command.substring(2).toInt() * (command.charAt(1) == '-' ? -1 : 1);
    moveMotors(Sides::Left, currentLeftSpeed);
  }
  else if (base == 'R')
  {
    int currentRightSpeed = command.substring(2).toInt() * (command.charAt(1) == '-' ? -1 : 1);
    moveMotors(Sides::Right, currentRightSpeed);
  }
  else if (base == 'A')
  {
    int action = String(command.charAt(1)).toInt();
    switch (action)
    {
    default:
      break;
    }
    // Do actions
  }
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
  for (int i = 0; i < NUM_LEDS; i++)
  {
    leds[i] = CRGB::Black;
  }
  FastLED.show();
}
#include "main.hpp"

CRGB leds[NUM_LEDS];
SSD1306Wire display(DISPLAY_ADDRESS, SDA, SCL);
Adafruit_HMC5883_Unified mag = Adafruit_HMC5883_Unified(12345);

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
  while (!mag.begin())
    ;

  setSonarPingSpeed(100);
  // Done initializing
  printString("Ready!");
}

// Loop function
void loop()
{
  delay(200);
  sensors_event_t event;
  mag.getEvent(&event);
  
  Serial.print("X: "); Serial.print(event.magnetic.x); Serial.print("  ");
  Serial.print("Y: "); Serial.print(event.magnetic.y); Serial.print("  ");
  Serial.print("Z: "); Serial.print(event.magnetic.z); Serial.print("  ");Serial.println("uT");
  float heading = atan2(event.magnetic.y, event.magnetic.x);
  
  // Once you have your heading, you must then add your 'Declination Angle', which is the 'Error' of the magnetic field in your location.
  // Find yours here: http://www.magnetic-declination.com/
  // Mine is: -13* 2' W, which is ~13 Degrees, or (which we need) 0.22 radians
  // If you cannot find your Declination, comment out these two lines, your compass will be slightly off.
  float declinationAngle = 0.22;
  heading += declinationAngle;
  
  // Correct for when signs are reversed.
  if(heading < 0)
    heading += 2*PI;
    
  // Check for wrap due to addition of declination.
  if(heading > 2*PI)
    heading -= 2*PI;
   
  // Convert radians to degrees for readability.
  float headingDegrees = heading * 180/M_PI; 
  
  Serial.print("Heading (degrees): "); Serial.println(headingDegrees);

  /*
  auto line = readLine();
  auto toPrint = String(line.a);
  toPrint.concat(" ");
  toPrint.concat(line.b);
  toPrint.concat(" ");
  toPrint.concat(line.c);
  printString(toPrint);

  if (!line.a && !line.c)
  {
    moveAllMotors(50);
  }
  else if (line.a && line.c)
  {
    moveAllMotors(0);
  }
  else if (line.a)
  {
    moveMotors(Left, -80);
    moveMotors(Right, 80);
  }
  else if (line.c)
  {
    moveMotors(Right, -80);
    moveMotors(Left, 80);
  }*/

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
  display.setFont(ArialMT_Plain_16);
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
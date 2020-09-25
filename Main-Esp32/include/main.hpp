#include <Arduino.h>
#include <Wire.h>
#include <FastLED.h>
#include <U8g2lib.h>
#include <SSD1306Wire.h>
#include "motor.hpp"
#include "servosensor.hpp"

#pragma once

#define BUTTON_PIN 0

#define SDA 4
#define SCL 15

#define OLED_RST 16

#define DISPLAY_ADDRESS 0x3c

#define NUM_LEDS 10
#define DATA_PIN 17

#define RGB_ADDRESS 0x20
#define RGB_COUNT 10

void printString(String string);

void initDisplay();
void initLeds();
#include <Arduino.h>
#include <Wire.h>
#include "SSD1306.h"
#include "motor.hpp"
#include <FastLED.h>

#pragma once

#define SDA 4
#define SCL 15

#define OLED_RST 16

#define DISPLAY_ADDRESS 0x3c

#define RGB_ADDRESS 0x20
#define RGB_COUNT 10

void initDisplay();
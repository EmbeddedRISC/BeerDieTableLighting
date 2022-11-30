/*************************************************************************
 * Arduino Code for BeerDieTableLighting (using Piezo detection and WS2811)
 * Copyright (C) <year>  <name of author>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 ***************************************************************************/
// First simple implementation used 1619 bytes
// Second implementation used 745 bytes

#include "SmartLED.h"

/////////////////////////////////////////////////////////////////////////////
// Definitions and Global Variables
/////////////////////////////////////////////////////////////////////////////

#define SERIAL_DEBUG

// LEDs
#define LED_REFRESH_RATE_MS 50
#define TRANSITION_TIME_MS (short)500
#define EFFECT_RATE 20

#define LED_STRING_LEN      50
#define BLUE_SIDE_LED_PIN   4
#define ORANGE_SIDE_LED_PIN 3

LedChain<LED_STRING_LEN, BLUE_SIDE_LED_PIN> blue_leds(TRANSITION_TIME_MS, LED_REFRESH_RATE_MS, EFFECT_RATE);
LedChain<LED_STRING_LEN, ORANGE_SIDE_LED_PIN> orange_leds(TRANSITION_TIME_MS, LED_REFRESH_RATE_MS, EFFECT_RATE);

CRGB leds[LED_STRING_LEN];

// Vib Sensor
#define VIB_SENSOR_PIN A0

/////////////////////////////////////////////////////////////////////////////
// Code Body
/////////////////////////////////////////////////////////////////////////////

// Entry point
void setup() {
  #ifdef SERIAL_DEBUG
    Serial.begin(500000);
  #endif

  // Initialize Randomization
  randomSeed(analogRead(A4));

  // Setup the Vib Sensor

  // Setup the LED Interfaces

  blue_leds.init();
  blue_leds.setAlternating(CRGB::Blue, CRGB::Purple);
  orange_leds.init();
  orange_leds.setAlternating(CRGB::Orange, CRGB::Red);

  blue_leds.animation = TWINKLE;
  orange_leds.animation = TWINKLE;

  FastLED.show();
}

// Main Program Loop
void loop() {
  int vib_val = analogRead(VIB_SENSOR_PIN);
  // Serial.println(vib_val);

  blue_leds.loop();
  orange_leds.loop();
  FastLED.show();

  delay(LED_REFRESH_RATE_MS);
}

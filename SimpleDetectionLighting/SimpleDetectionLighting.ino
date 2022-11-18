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

#include "FastLED.h"

/////////////////////////////////////////////////////////////////////////////
// Definitions and Global Variables
/////////////////////////////////////////////////////////////////////////////

#define SERIAL_DEBUG

// LEDs
#define LED_STRING_LEN      50
#define BLUE_SIDE_LED_PIN   4
#define ORANGE_SIDE_LED_PIN 3

CRGB blue_side_leds[LED_STRING_LEN];
CRGB orange_side_leds[LED_STRING_LEN];

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

  // Setup the Vib Sensor

  // Setup the LED Interfaces
  FastLED.addLeds<WS2811, BLUE_SIDE_LED_PIN>(blue_side_leds, LED_STRING_LEN);
  FastLED.addLeds<WS2811, ORANGE_SIDE_LED_PIN>(orange_side_leds, LED_STRING_LEN);
  reset_lights();
}

// Main Program Loop
void loop() {
  int vib_val = analogRead(VIB_SENSOR_PIN);  
  
  Serial.println(vib_val);
}


/////////////////////////////////////////////////////////////////////////////
// Helper Functions
/////////////////////////////////////////////////////////////////////////////

// Reset the lighting effects to the default
void reset_lights() {
  #ifdef SERIAL_DEBUG
    Serial.println("reset_lights");  
  #endif

  for (int i = 11; i < 20; i++) {
    blue_side_leds[i] = CRGB::Purple;
    orange_side_leds[i] = CRGB::Orange;
  }
  FastLED.show();
}

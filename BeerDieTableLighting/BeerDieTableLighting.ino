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
#include "SPI.h"

/////////////////////////////////////////////////////////////////////////////
// Definitions and Global Variables
/////////////////////////////////////////////////////////////////////////////

#define SERIAL_DEBUG

// LEDs
#define LED_STRING_LEN      50
#define BLUE_SIDE_LED_PIN   10
#define ORANGE_SIDE_LED_PIN 11

CRGB blue_side_leds[LED_STRING_LEN];
CRGB orange_side_leds[LED_STRING_LEN];

// ADC
#define HIT_VAL    100
#define ADC_CS_PIN 9

short adc_vals[2];


/////////////////////////////////////////////////////////////////////////////
// Code Body
/////////////////////////////////////////////////////////////////////////////

// Entry point
void setup() {
  #ifdef SERIAL_DEBUG
    Serial.begin(500000);
  #endif
  
  // Setup the SPI Interface
  SPI.begin();
  
  // Setup the LED Interfaces
  FastLED.addLeds<WS2811, BLUE_SIDE_LED_PIN>(blue_side_leds, LED_STRING_LEN);
  FastLED.addLeds<WS2811, ORANGE_SIDE_LED_PIN>(orange_side_leds, LED_STRING_LEN);
  reset_lights();
}

// Main Program Loop
void loop() {

}

/////////////////////////////////////////////////////////////////////////////
// Helper Functions
/////////////////////////////////////////////////////////////////////////////

// Reset the lighting effects to the default
void reset_lights() {
  #ifdef SERIAL_DEBUG
    Serial.println("reset_lights");  
  #endif

  for (int i = 0; i < LED_STRING_LEN; i++) {
    blue_side_leds[i] = CRGB::Purple;
    orange_side_leds[i] = CRGB::Orange;
  }
  FastLED.show();
}

void blue_hit_lights() {
  #ifdef SERIAL_DEBUG
    Serial.println("blue_hit_lights");  
  #endif

  for (int i = 0; i < LED_STRING_LEN; i++) {
    blue_side_leds[i] = CRGB::Orange;
    orange_side_leds[i] = CRGB::Orange;
  }
  FastLED.show();
}

void orange_hit_lights() {
  #ifdef SERIAL_DEBUG
    Serial.println("orange_hit_lights");  
  #endif

  for (int i = 0; i < LED_STRING_LEN; i++) {
    blue_side_leds[i] = CRGB::Purple;
    orange_side_leds[i] = CRGB::Purple;
  }
  FastLED.show();
}

void middle_hit_lights() {
  #ifdef SERIAL_DEBUG
    Serial.println("middle_hit_lights");  
  #endif

  for (int i = 0; i < LED_STRING_LEN; i++) {
    blue_side_leds[i] = CRGB::Green;
    orange_side_leds[i] = CRGB::Green;
  }
  FastLED.show();
}

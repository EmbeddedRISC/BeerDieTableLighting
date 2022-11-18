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
#define BLUE_SIDE_LED_PIN   2
#define ORANGE_SIDE_LED_PIN 3

CRGB blue_side_leds[LED_STRING_LEN];
CRGB orange_side_leds[LED_STRING_LEN];

// ADC
#define HIT_THRESHOLD 100
#define SIDE_HIT_DIFF 25
#define ADC_CS_PIN    9

#define BLUE_ADC_IDX   0
#define ORANGE_ADC_IDX 1

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
  SPI.setClockDivider(SPI_CLOCK_DIV2);
  SPI.setDataMode(SPI_MODE3);
  
  // Setup the LED Interfaces
  FastLED.addLeds<WS2811, BLUE_SIDE_LED_PIN>(blue_side_leds, LED_STRING_LEN);
  FastLED.addLeds<WS2811, ORANGE_SIDE_LED_PIN>(orange_side_leds, LED_STRING_LEN);
  reset_lights();
}

// Main Program Loop
void loop() {
  read_adc();
  
  if ((adc_vals[BLUE_ADC_IDX] > HIT_THRESHOLD) && (adc_vals[ORANGE_ADC_IDX] > HIT_THRESHOLD)) {
    if (adc_vals[BLUE_ADC_IDX] > adc_vals[ORANGE_ADC_IDX] + SIDE_HIT_DIFF) {
      blue_hit();
    }
    else if (adc_vals[ORANGE_ADC_IDX] > adc_vals[BLUE_ADC_IDX] + SIDE_HIT_DIFF) {
      orange_hit();
    }
    else {
      middle_hit();
    }
  }
  else if (adc_vals[BLUE_ADC_IDX] > HIT_THRESHOLD) {
    blue_hit();
  }
  else if (adc_vals[ORANGE_ADC_IDX] > HIT_THRESHOLD) {
    orange_hit();
  }
  
}

void blue_hit() {
  blue_hit_lights();
  delay(1000);
  reset_lights();
}
      
void orange_hit() {
  orange_hit_lights();
  delay(1000);
  reset_lights();
}

void middle_hit() {
  middle_hit_lights();
  delay(1000);
  reset_lights();
}

/////////////////////////////////////////////////////////////////////////////
// Helper Functions
/////////////////////////////////////////////////////////////////////////////

// Fetch the ADC Data
void read_adc() {
  digitalWrite(SS, LOW);
  adc_vals[BLUE_ADC_IDX] = SPI.transfer16(0);
  adc_vals[ORANGE_ADC_IDX] = SPI.transfer16(0);
  digitalWrite(SS, HIGH);
  // TODO: Convert 12-bit 2's Complement to 16-bit
  
  #ifdef SERIAL_DEBUG
    Serial.print("ADC0-Blue: ");
    Serial.println(String(adc_vals[BLUE_ADC_IDX], HEX));
    Serial.print("ADC-Orange: ");
    Serial.println(String(adc_vals[ORANGE_ADC_IDX], HEX));
  #endif
  
  if (adc_vals[BLUE_ADC_IDX] & 0x800) {
    adc_vals[BLUE_ADC_IDX] |= 0xF000;    
  }

  if (adc_vals[ORANGE_ADC_IDX] & 0x800) {
    adc_vals[ORANGE_ADC_IDX] |= 0xF000;
  }

  #ifdef SERIAL_DEBUG
    Serial.print("ADC0-Blue: ");
    Serial.println(adc_vals[BLUE_ADC_IDX]);
    Serial.print("ADC-Orange: ");
    Serial.println(adc_vals[ORANGE_ADC_IDX]);
    Serial.println();
  #endif

  delay(2000);
}

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

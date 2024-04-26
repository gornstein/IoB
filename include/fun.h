//fun.h
// Has all functions
#ifndef FUN_H
#define FUN_H

#include "include.h"

volatile int pulseCount = 0;

void setStrip(int program) {
  switch (program) {
      case 0: // General and Initializing
        // LEDs -> White
        for (int i = 0; i < numPixels; i++){
          strip.setPixelColor(i, 255, 255, 255);
          delay(200);
          strip.show();
        }
        buttonLED.fadeIn(255,255,255,20,3);
        strip.show();
        break;
      
      case 1: // Off
        // LEDs -> Off
        strip.fill();
        buttonLED.off();
        break;
      
      case 2: // Rate limiting
        // LEDs -> Flashing
        buttonLED.flash(RGBLed::RED, 250);
        strip.fill();
        break;

      case 3: // Dispensing
        // LEDs -> Pulsing
        buttonLED.crossFade(RGBLed::GREEN,RGBLed::BLUE,20,2500);
        updateStripColor(64,64,64);
        strip.setPixelColor(2,255,255,255);
        strip.setPixelColor(5,255,255,255);
        strip.show();
        break;

      case 4: // Ready to dispense
        buttonLED.crossFade(RGBLed::BLUE,RGBLed::WHITE,20,2500);
        updateStripColor(64,64,64);
        strip.show();
        break;
    }
}

void updateStripColor(int red, int green, int blue) { // Sets RGB levels for each LED
  for (int i = 0; i < numPixels; i++) {
    strip.setPixelColor(i, red, green, blue);
  }
  //strip.show();
}

void dispenseBeverage() {
  unsigned long startDispenseTime = millis();
  pulseCount = 0;
  while (float flowRate = getFlow()){
    if (!(-0.5 < flowRate < 0.5)) break; // ENDFLOW
    if 
  }
}

ICACHE_RAM_ATTR void countPulse(){
  pulseCount++;
}

float getFlow(){
  
}

#endif

(TIMEOUT || LIMIT || ENDFLOW)
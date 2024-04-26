//fun.h
// Has all functions
#ifndef FUN_H
#define FUN_H

#include "include.h"

volatile int pulseCount = 0;
bool stepperState = 1; // TRUE = Closed. Assume stepper is starting in open state

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
  while (true){
    if (pulseCount >= dispenseLimitPulses){ // Dispense limit reached
      
    }
  }
}

ICACHE_RAM_ATTR void countPulse(){
  pulseCount++;
}

void setValve(bool state){
  if (state) { // Open -> Closed
    if (stepperState) return; // Check if stepper is already closed
    digitalWrite(stepperEnPin, LOW); // Turn stepper motor on
    for (int i = 0; i < stepsQuarterTurn; i++){ // Step through number of steps for a quarter turn
      digitalWrite(stepperPin, HIGH);
      delay(1);
      digitalWrite(stepperDirPin, LOW);
      delay(1);
    }
    digitalWrite(stepperEnPin, HIGH); // Turn stepper motor off
    stepperState = 1; // Remember that the valve is now closed
    return;
  }
  if (!state) { // Closed -> Open
    if (!stepperState) return; // Check if stepper is already open
    digitalWrite(stepperDirPin, HIGH); // Switch direction
    digitalWrite(stepperEnPin, LOW); // Enable stepper motor
    for (int i = 0; i < stepsQuarterTurn; i++){ // Step through number of steps for a quarter turn
      digitalWrite(stepperPin, HIGH);
      delay(1);
      digitalWrite(stepperDirPin, LOW);
      delay(1);
    }
    digitalWrite(stepperEnPin, HIGH); // Disable stepper motor
    digitalWrite(stepperDirPin, LOW); // Reset direction pin
    stepperState = 0;
    return;
  }
}

#endif
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
  strip.show();
}

void dispenseBeverage() { // Main function for handling drink dispensing functionality. Triggered by a flow of liquid through the flow sensor since the valve is normally open
  unsigned long startDispenseTime = millis();
  unsigned long lastMillis2 = 0; // Keep track of time since last checked pulses per second
  int pulseCount2 = pulseCount; // To keep track of delta pulseCount
  int pulsesPerSecond2 = 0; // Pulses per second during dispensing
  Serial.println("Stupid fuck got thirsty - dispensing bev...");
  while (true){
    unsigned long currentMillis = millis();
    if (pulseCount >= dispenseLimitPulses){ // Dispense limit reached
      Serial.println("Needy whore is dispensing too much - closing valve...");
      setValve(1); // Shut valve
      cooldown();
      return;
    }
    else if (currentMillis - startDispenseTime >= dispenseTimeout){
      Serial.println("Dumb idiot is taking too long - timing out (returning to loop)");
      return;
    }
    else if (currentMillis - lastMillis2 >= 500) { // If bev stops flowing, user must be done dispensing so return to main loop without shutting valve
      pulsesPerSecond2 = (pulseCount - pulseCount2) * 2;
      lastMillis2 = currentMillis;
      Serial.println("Pulses per second: " + pulsesPerSecond2);
      if (pulsesPerSecond2 <= pulseTriggerSensitivity){ // Bev stopped flowing
        Serial.println("Bev has stopped flowing, returning to main loop");
        return;
      }
      pulseCount2 = pulseCount;
    }
    
  }
}

ICACHE_RAM_ATTR void countPulse(){ // Triggered by flow sensor HW interrupt - each pulse rising edge increments pulseCount by one
  pulseCount++;
}

void setValve(bool state){ // State = 1 closes the valve; State = 0 opens the valve. Valve is normally open
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

void cooldown(){ // Used after a valve-close condition is met to wait a few seconds for the thirsty fuck to leave the dispenser before reopening the valve
  Serial.println("Timing out while thirsty fuck leaves before reopening valve");
  delay(dispenseCooldown);
  Serial.println("Timeout is over - reopening valve");
  setValve(0);
  return;
}

#endif
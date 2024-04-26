// Internet of Borg 2.0 software
// Created by Graham Ornstein gh@gornstein

#include "include.h"

void setup() {
  Serial.begin(115200);
  Serial.println("HOPE YOU'RE THIRSTY (starting up)");
  Serial.println("Initializing pins...");
  initializePins();

}
unsigned long lastMillis = 0;
int pulsesPerSecond = 0;

void loop() {
  unsigned long currentMillis = millis(); // Get initial time
  // if (currentMillis - lastMillis >= 500) { // Calculate pulses per half second and multiply by two
  //   pulsesPerSecond = pulseCount * 2;
  //   lastMillis = currentMillis;
  //   Serial.println("Pulses per second: " + pulsesPerSecond);
  //   if (pulsesPerSecond >= pulseTriggerSensitivity) dispenseBeverage(); // If liquid start flowing run dispenseBeverage
  //   pulseCount = 0; // Reset pulseCount for next iteration
  // }
  setValve(1);
  delay(3000);
  setValve(0);
  delay(5000);
}
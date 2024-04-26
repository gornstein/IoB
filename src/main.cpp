// Internet of Borg 2.0 software

#include "include.h"

void setup() {
  Serial.begin(115200);
  Serial.println("Starting up...");
  Serial.println("Initializing pins...");
  initializePins();

}
unsigned long lastMillis = 0;
int pulsesPerSecond = 0;

void loop() {
  unsigned long currentMillis = millis(); // Get initial time
  if (currentMillis - lastMillis >= 500) { // Calculate pulses per half second and multiply by two
    pulsesPerSecond = pulseCount * 2;
    lastMillis = currentMillis;
    Serial.printf("\n\rPulses per second: %d",pulsesPerSecond);
    if (pulsesPerSecond >= pulseTriggerSensitivity) dispenseBeverage();
    pulseCount = 0;
  }

}
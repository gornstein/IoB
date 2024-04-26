// io.h
// Initializes and configures IO definitions

#ifndef IO_H
#define IO_H

#include "include.h"

//------- Define GPIO
const int flowSensorPin = D8; // Flow sensor signal
const int btnPin = D3; // Button input
const int stripPin = D4; // LED Strip

// Stepper Driver
const int stepperPin = D0;
const int stepperEnPin = D1;
const int stepperDirPin = D2;

// Button LEDs
const int btnRed = D5;
const int btnGreen = D6;
const int btnBlue = D7;
//--------

const int numPixels = 8; // Number of LEDs on strip

Adafruit_NeoPixel strip = Adafruit_NeoPixel(numPixels, stripPin, NEO_GRB + NEO_KHZ800);
RGBLed buttonLED(btnRed, btnGreen, btnBlue, RGBLed::COMMON_CATHODE);


void initializePins() {
  pinMode(stepperPin, OUTPUT);
  pinMode(stepperEnPin, OUTPUT);
	digitalWrite(stepperEnPin, HIGH);
  pinMode(stepperDirPin, OUTPUT);

  pinMode(flowSensorPin, INPUT);
	attachInterrupt(digitalPinToInterrupt(flowSensorPin), countPulse, RISING);

  pinMode(btnPin, INPUT_PULLUP);
  pinMode(btnRed, OUTPUT);
  pinMode(btnGreen, OUTPUT);
  pinMode(btnBlue, OUTPUT);
    
  strip.begin();
  strip.setBrightness(50);
  strip.clear();
  strip.show(); // Initialize all pixels to off
}

#endif
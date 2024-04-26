// settings.h
// Definitions for tweakable variables

#ifndef SETTINGS_H
#define SETTINGS_H

// Calibration values
const float flowCal = 5880.0; //Pulses/liter
const float ouncesPerLiter = 33.814;

// Defaults
const int dispenseLimit = 10; // This is the main setting for the dispensing amount limit. Value is flOz
const int dispenseTimeout = 10000; // Time in ms
const int pulseTriggerSensitivity = 20; // How many pulses will trigger dispenseBeverage
const int stepsPerRotation = 80; // Stepper motor steps per full rotation (from datasheet)

#define dispenseLimitLiters (dispenseLimit * ouncesPerLiter) // Convert ounces to liters
#define dispenseLimitPulses (dispenseLimitLiters * flowCal) // Convert liters to pulses of flow sensor
#define stepsQuarterTurn (stepsPerRotation / 4) // Get number of steps to open and close valve

#endif
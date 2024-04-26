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

#define dispenseLimitLiters (dispenseLimit * ouncesPerLiter) // Convert ounces to liters
#define dispenseLimitPulses (dispenseLimitLiters * flowCal) // Concert liters to pulses of flow sensor

#endif
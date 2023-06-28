// io.h
// Initializes and configures IO definitions
#include <Adafruit_NeoPixel.h>

//------- Define GPIO
const int solenoidPin = 16; //Relay driving solenoid
const int flowSensor = 5;
const int btnPin = 4; //Button input
const int stripPin = 2; //LED Strip
//Button LEDs:
const int btnRed = 14;
const int btnGreen = 12;
const int btnBlue = 13;

//--------
const int numPixels = 8; //Number of LEDs on strip

Adafruit_NeoPixel strip = Adafruit_NeoPixel(numPixels, stripPin, NEO_GRB + NEO_KHZ800);
RGBLed buttonLED(btnRed, btnGreen, btnBlue, RGBLed::COMMON_CATHODE);


void initializePins() {
    pinMode(solenoidPin, OUTPUT);
    pinMode(flowSensor, INPUT);
    pinMode(btnPin, INPUT);
    pinMode(btnRed, OUTPUT);
    pinMode(btnGreen, OUTPUT);
    pinMode(btnBlue, OUTPUT);
    
    strip.begin();
    strip.setBrightness(50);
    strip.show(); //Initialize all pixels to off
}
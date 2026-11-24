#include "init_system.hpp"

SystemInit::SystemInit(int pinPot, int pinLdr, Adafruit_NeoPixel& ring) : PIN_POT(pinPot), PIN_LDR(pinLdr), lamp(ring) {}

void SystemInit::begin()
{
    pinMode(PIN_POT, INPUT);
    pinMode(PIN_LDR, INPUT);

    lamp.begin();
    lamp.clear();
    lamp.fill(lamp.Color(255, 255, 255)); //white 
}

void SystemInit::setupSerial(int baud)
{
    Serial.begin(baud);
    while(!Serial) {}
    Serial.println("[SERIAL] Serial communication for debug active.\n");
}


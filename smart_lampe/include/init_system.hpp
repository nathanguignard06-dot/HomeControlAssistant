#ifndef INIT_SYSTEME
#define INIT_SYSTEME

#include <Arduino.h>
#include <Adafruit_NeoPixel.h>

class SystemInit
{
    public:

        SystemInit(int pinPot, int pinLdr, Adafruit_NeoPixel& ring);

        void begin();
        void setupSerial(int baud);
        

    private:

        const int PIN_POT;
        const int PIN_LDR;

        Adafruit_NeoPixel& lamp;
};

#endif
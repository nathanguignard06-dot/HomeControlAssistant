#ifndef DATAREADING
#define DATAREADING

#include "init_system.hpp"
#include "MqttCommunication.hpp"
#include <ESPmDNS.h>
#include <Update.h>
#include <esp_mac.h>

class DataReading
{
    public:

        DataReading(SystemInit& system, MqttCommunication& mqttClient, Adafruit_NeoPixel& ring);

        String requestMacAddress();
        int requestBrightness();
        int requestPotValue();
        int requestLdrValue();
        unsigned long requestTime();
        void controlNeopixel();
        
        private:

        String deviceId;
        String currentMode;
        int brightness;
        int potValue;
        int ldrValue;
        
        SystemInit& lampeSystem;
        Adafruit_NeoPixel& lamp;
        MqttCommunication& mqtt;        
};
#endif
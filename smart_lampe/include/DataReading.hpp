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

        DataReading(SystemInit& system, MqttCommunication& mqttClient);

        String requestMacAddress();
        int requestBrightness();
        int requestPotValue();
        int requestLdrValue();
        
        private:

        String deviceId;
        String currentMode;
        int brightness;
        int potValue;
        int ldrValue;
        
        SystemInit& lampeSystem;
        MqttCommunication& mqtt;        
};
#endif
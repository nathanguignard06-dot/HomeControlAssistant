#include "DataReading.hpp"

DataReading::DataReading(SystemInit& system, MqttCommunication& mqttClient, Adafruit_NeoPixel& ring) : lampeSystem(system), mqtt(mqttClient), lamp(ring) {}

String DataReading::requestMacAddress()
{
    uint8_t mac[6];
    esp_read_mac(mac, ESP_MAC_WIFI_STA);

    char macString[18];
    snprintf(macString, sizeof(macString),
            "%02X:%02X:%02X:%02X:%02X:%02X",
            mac[0], mac[1], mac[2],
            mac[3], mac[4], mac[5]);

    deviceId = String(macString);

    return deviceId;
}

int DataReading::requestBrightness()
{
    switch(mqtt.currentModeActive())
    {
        case ControlMode::POTENTIOMETER:
            brightness = potValue;
            currentMode = "POTENTIOMETER";
            break;
        case ControlMode::DASHBOARD:
            brightness = mqtt.requestDashValue();
            currentMode = "DASHBOARD";
            break;
        case ControlMode::AUTO:
            brightness = mqtt.requestAutoValue();
            currentMode = "AUTO";
            break;
    }

    return brightness;
}

int DataReading::requestPotValue()
{
    potValue = lampeSystem.readPot();
    return potValue;
}

int DataReading::requestLdrValue()
{
    ldrValue = lampeSystem.readLdr();
    return ldrValue;
}

unsigned long DataReading::requestTime()
{
    return millis();
}

void DataReading::controlNeopixel()
{
    lamp.clear();
    lamp.fill(lamp.Color(255, 255, 255)); //white
    lamp.setBrightness(brightness);
    lamp.show();
}
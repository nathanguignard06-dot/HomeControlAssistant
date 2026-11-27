#include "Init_system.hpp"

Init_system::Init_system(Oled& screen, int baud) : oled(screen), SERIAL_BAUD_R8(baud) {}

void Init_system::begin()
{
    setupSerial(SERIAL_BAUD_R8);
    if(!oled.begin())
    {
        Serial.println("[OLED] Restarting allocation");
        oled.begin();
    }

    Serial.println("[OLED] Oled ready");
}

void Init_system::setupSerial(int baud)
{
    Serial.begin(baud);
    while(!Serial) {}
    Serial.println("[SERIAL] Serial monitor ready");
}
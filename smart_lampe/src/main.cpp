#include "WiFiConnect.hpp"

WiFiConnect wifi("ESP32_SETUP");

bool applicationStarted = false;


void setup()
{
  Serial.begin(115200);

  if(wifi.begin())
  {
    Serial.println("[SYSTEM] WiFi ready!");

    //starting application
    applicationStarted = true;
  }
}


void loop()
{
  if(!applicationStarted)
  {
    wifi.handleClient();

    //check if the user successfully configured WiFi
    if (wifi.isConnected())
    {
      Serial.println("[SYSTEM] WiFi configured!");

      //starting application
      applicationStarted = true;
    }
  }

  if(applicationStarted)
  {
    //later code goes here

  }
}
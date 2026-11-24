#include "include_all.h"

SystemInit lampeSystem(POT_PIN, LDR_PIN, ring);
WiFiConnect wifi("ESP32_SETUP");
MqttClient client;
MqttCommunication mqtt(broker, port, client);
DataReading object(lampeSystem, mqtt, ring);

bool applicationStarted = false;

//application initializer
void startApplication()
{
  Serial.println("[SYSTEM] Starting application...");

  mqtt.begin();
  lampeSystem.begin();

  applicationStarted = true;

  Serial.println("[SYSTEM] Application started!");
}

void setup()
{
  lampeSystem.setupSerial(baud);  //init serial communication for debug

  if(wifi.begin())
  {
    Serial.println("[SYSTEM] WiFi ready!");

    //starting application
    startApplication();
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
      startApplication();
    }
  }

  if(applicationStarted)
  {
    mqtt.poll();
    //later code goes here

  }
}
#include "include_all.h"

/*--- OBJECT INITIALISING ---*/
SystemInit lampeSystem(POT_PIN, LDR_PIN, ring);
WiFiConnect wifi("ESP32_SETUP");
WiFiClient networkClient;
MqttClient client(networkClient);
MqttCommunication mqtt(broker, port, client);
DataReading object(lampeSystem, mqtt, ring);

/*--- GLOBAL VARIABLES ---*/
bool applicationStarted          = false;   //to start app

const long interval              = 1000;    //interval for ldr reading and rest of program
unsigned long previousMillis     = 0;
const long intervalPot           = 20;       //interval for potentiometer reading
unsigned long previousMillisPot  = 0;
const long intervalSend          = 50000;   //interval for sending data
unsigned long previousMillisSend = 0;
unsigned long previousMillisAuto = 0;

String deviceID                  = "";      //mac address stored in this variable acting as a device id
int potValue                     = 0;
int ldrValue                     = 0;
int brightness                   = 0;
unsigned long timestamp          = 0;

//application initializer
void startApplication()
{
  Serial.println("[SYSTEM] Starting application...");

  mqtt.begin();
  lampeSystem.begin();
  deviceID = object.requestMacAddress();

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
    
    unsigned long currentMillisPot = millis();
    unsigned long currentMillis = millis();
    if(currentMillisPot - previousMillisPot >= intervalPot)
    {
      previousMillisPot = currentMillisPot;

      potValue = object.requestPotValue();      //reading pot value

      brightness = object.requestBrightness();  //retrieving brightness

      object.controlNeopixel();                 //affecting light brightness according to brightness
    }

    if(currentMillis - previousMillis >= interval)
    {
      previousMillis = currentMillis;

      timestamp = object.requestTime();

      ldrValue = object.requestLdrValue();

      unsigned long currentMillisSend = millis();
      if(currentMillisSend - previousMillisSend >= intervalSend)
      {
        previousMillisSend = currentMillisSend;

        JsonDocument doc;

        doc["deviceID"] = deviceID;
        doc["deviceLocation"] = WiFi.localIP().toString();
        doc["photoValue"] = ldrValue;
        doc["potentiometerValue"] = potValue;
        doc["brightness"] = brightness;
        doc["controlMode"] = mqtt.getModeString();
        doc["timestamp"] = timestamp;
        doc["deviceType"] = "Neopixel 24 LED's Ring";

        String json;
        serializeJson(doc, json);

        mqtt.publish(json, MqttTopics::allData);
      }
    }
  }
}
#include "include_all.h"

/*
*   example code for using WiFiConnect class
*/

/*--- DEFINITIONS ---*/
//not needed if not using Oled.hpp functionalities
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64    //this can change depending on oled type

//microphone configs
#define MIC_SCK 26
#define MIC_WS  25
#define MIC_SD  33

/*---DECLARATIONS---*/
//for Oled.hpp
Adafruit_SSD1306 screen(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);
Oled oled(screen);

WiFiConnect wifi("ESP32_SETUP", oled);

Microphone microphone(MIC_SCK, MIC_WS, MIC_SD, 16000);

/*--- GLOBAL VARIABLES ---*/
bool applicationStarted      = false;   //to start app
bool microphoneReady         = false;   //microphone state

//application initializer
void startApplication()
{
  Serial.println("[SYSTEM] Starting application...");

  //all initialisations go in here (example : pinMode(LED_BUILTIN, LOW))
  microphoneReady = microphone.begin();

  if(!microphoneReady)
  {
    Serial.println("[MIC] Initialization failed");
  }

  applicationStarted = true;

  Serial.println("[SYSTEM] Application started!");
}

void setup()
{
    //always start serial monitor, and other debug or visualising methods before wifi.begin()
    Serial.begin(115200);
    while(!Serial) {}
    Serial.println("\nSerial communication started");

    oled.begin();   //comment if not using Oled.hpp functionalities

    delay(1000);

    if(wifi.begin())
    {
        Serial.println("[SYSTEM] WiFi ready");
        startApplication();
    }
}

void loop()
{
    if(!applicationStarted)
    {
        wifi.handleClient();

        //check if the user successfully configured WiFi
        if(wifi.isConnected())
        {
            oled.clearScreen();
            oled.screenSettings(1, 0, 6);
            Serial.println("[SYSTEM] WiFi configured!");
            oled.print("WiFi configured!");
            oled.screenSettings(1, 0, 16);
            oled.print("Starting application");
            oled.displayScreen();
            delay(1000);

            startApplication();
        }
    }
    if(applicationStarted && microphoneReady)
    {
        static int32_t audioBuffer[256];

        size_t samplesRead = 0;

        if(microphone.read(audioBuffer, 256, samplesRead))
        {
            int64_t peak = 0;

            for(size_t i = 0; i < samplesRead; i++)
            {
                int64_t value = audioBuffer[i];

                if(value < 0)
                    value = -value;

                if(value > peak)
                    peak = value;
            }

            static unsigned long previousMillis = 0;

            if(millis() - previousMillis >= 500)
            {
                previousMillis = millis();

                Serial.print("[MIC] Samples: ");
                Serial.print(samplesRead);

                Serial.print(" | Peak: ");
                Serial.println((long long)peak);
            }
        }
    }
}
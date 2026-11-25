#ifndef WIFICONNECT
#define WIFICONNECT

#include <Arduino.h>
#include <WiFi.h>
#include <WiFiClient.h>
#include <WebServer.h>
#include <Preferences.h>

class WiFiConnect
{
    public:

        WiFiConnect(const char ssidAP[]);

        bool begin();

        void wifiAPmode();
        void getAPIP();
        bool wifiConnectToRouter(const char ssid[], const char pass[]);
        void handleClient();
        bool isConnected();

    private:

        const char* SSID_AP;        
        IPAddress IP;
        WebServer server;
        Preferences preferences;

        void handleRoot();
        void handleCredentials();

};
#endif
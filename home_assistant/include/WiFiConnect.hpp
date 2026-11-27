#ifndef WIFICONNECT
#define WIFICONNECT

#include <WiFi.h>
#include <WiFiClient.h>
#include <WebServer.h>
#include <Preferences.h>
#include "Oled.hpp"         //Oled class (optional)

class WiFiConnect
{
    public:

        /**
         * @brief WiFiConnect class constructor.
         *
         * @param const char ssidAP[]   : Acting as the name of the hotspot ssid.
         * @param Oled& screen          : Getting the oled screen object to allow usage of Oled class
         */
        WiFiConnect(const char ssidAP[], Oled& screen);     //comment Oled& screen if you dont want to implement Oled fonctionalities
    
        /**
         * @brief Initialise the wifi connection.
         *
         * @return True if connection successful, false if unsuccessful (bool).
         */
        bool begin();

        /**
         * @brief Connecting as access point to retrieve user wifi ssid and password.
         *
         * @return Begins web server.
         */
        void wifiAPmode();

        /**
         * @brief Request the access point IP to connect to microcontroler.
         *
         * @return Access point IP address (string).
         */
        void getAPIP();

        /**
         * @brief Function to connect to the wifi using ssid and password given from user.
         *
         * @param const char ssid[]     : User ssid
         * @param const char pass[]     : User pass
         * @return False if connection not possible (bool), IP address of device if connection successful (string).
         */
        bool wifiConnectToRouter(const char ssid[], const char pass[]);

        /**
         * @brief Handles web server.
         */
        void handleClient();

        /**
         * @brief Verifies connection status.
         *
         * @return Wifi status.
         */
        bool isConnected();

        /**
         * @brief Request mac address of microcontroler.
         *
         * @return mac address (string).
         */
        void getMac();      //this function not needed if you are not using esp-now

    private:

        const char* SSID_AP;        
        IPAddress IP;
        WebServer server;
        Preferences preferences;
        String mac;         //comment if you are not using void getMac
        Oled& oled;         //comment if you are not using Oled.hpp and fonctionalities

        /**
         * @brief Html page for user to input ssid and password.
         */
        void handleRoot();

        /**
         * @brief Verifies for new credentials, stores credentials, and handles successful and unsuccessful conection html pages.
         */
        void handleCredentials();

};
#endif
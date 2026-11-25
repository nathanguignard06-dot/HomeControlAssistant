#ifndef MQTTCOMMUNICATION
#define MQTTCOMMUNICATION

#include "WiFiConnect.hpp"
#include "MqttTopics.hpp"
#include <ArduinoMqttClient.h>

enum class ControlMode
{
    POTENTIOMETER,
    DASHBOARD,
    AUTO
};

class MqttCommunication
{
    public:

        MqttCommunication(const char broker[], int port, MqttClient& client);

        bool begin();
        const ControlMode currentModeActive();
        int requestDashValue();
        int requestAutoValue();
        void poll();
        void publish(String json, const char topic[]);
        String getModeString();
        
    private:
        
        const char* BROKER;
        const int PORT;
        
        int dashboardBrightness = 0;
        int autoBrightness = 0;
        
        ControlMode currentMode = ControlMode::POTENTIOMETER;
        MqttClient& mqttClient;
        
        static MqttCommunication* instance;
        static void onMqttMessageCallback(int messageSize);
        void onMqttMessage(int messageSize);
        void onMessage();
        void subscribeToTopics();
};
#endif
#include "MqttCommunication.hpp"

MqttCommunication::MqttCommunication(const char broker[], int port, MqttClient& client) : BROKER(broker), PORT(port), mqttClient(client) {}

void MqttCommunication::begin()
{
    if(!mqttClient.connect(BROKER, PORT))
    {
        Serial.print("[MQTT] Connection failed! Error code = ");
        Serial.println(mqttClient.connectError());
    }

    onMessage();
    subscribeToTopics();
}

void MqttCommunication::subscribeToTopics()
{
    mqttClient.subscribe("light/control/#");
}

const ControlMode MqttCommunication::currentModeActive()
{
    return currentMode;
}

MqttCommunication* MqttCommunication::instance = nullptr;

void MqttCommunication::onMessage()
{
    instance = this;
    mqttClient.onMessage(onMqttMessageCallback);
}

void MqttCommunication::onMqttMessageCallback(int messageSize)
{
    if(instance != nullptr)
    {
        instance->onMqttMessage(messageSize);
    }
}

void MqttCommunication::onMqttMessage(int messageSize)
{
    // Retrieve topic BEFORE reading payload
    String receivedTopic = mqttClient.messageTopic();
    String payload = "";

    for(int i = 0; i < messageSize; i++)
    {
        if(mqttClient.available())
        {
            payload += (char)mqttClient.read();
        }
    }

    Serial.println("[MQTT] Message received");

    Serial.print("\n[MQTT] Topic: ");
    Serial.println(receivedTopic);

    Serial.print("[MQTT] Payload: ");
    Serial.println(payload);

    // Brightness command
    if(receivedTopic == MqttTopics::brightness)
    {
        int brightnessPercent = constrain(payload.toInt(), 0, 100);

        dashboardBrightness = map(brightnessPercent, 0, 100, 0, 255);

        Serial.print("[MQTT] Dashboard brightness: ");
        Serial.println(brightnessPercent);
    }

    // Control mode command
    else if(receivedTopic == MqttTopics::modeControl)
    {
        payload.trim();
        payload.toUpperCase();

        if (payload == "POTENTIOMETER")
        {
            currentMode = ControlMode::POTENTIOMETER;
        }
        else if (payload == "DASHBOARD")
        {
            currentMode = ControlMode::DASHBOARD;
        }
        else if(payload == "AUTO")
        {
            currentMode = ControlMode::AUTO;
        }

        Serial.print("[SYSTEM] Control mode changed to: ");
        Serial.println(payload);
    }
    else if(receivedTopic == MqttTopics::autoBrightness)
    {
        autoBrightness = constrain(payload.toInt(), 0, 255);
    }
}

void MqttCommunication::poll()
{
    mqttClient.poll();
}

int MqttCommunication::requestDashValue()
{
    return dashboardBrightness;
}

int MqttCommunication::requestAutoValue()
{
    return autoBrightness;
}

void MqttCommunication::publish(String json, const char topic[])
{
    mqttClient.beginMessage(topic);
    mqttClient.print(json);
    mqttClient.endMessage();
}
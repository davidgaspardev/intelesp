#ifndef MQTT_CLIENT_H
#define MQTT_CLIENT_H

#include <WiFi.h>
#include <PubSubClient.h>

class MqttClient {
private:
    bool initialized;
    IPAddress ip;
    uint16_t port;
    byte id[16]; // 16-bytes for client id
    PubSubClient core;
public:
    void setup(IPAddress, uint16_t);
    bool isConnected();
    bool connect();
    void reconnect();
    void checkConnection();

    bool publish(const char* topic, const char* msg);
};

#endif
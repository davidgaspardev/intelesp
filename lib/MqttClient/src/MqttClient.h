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
    MqttClient();
    MqttClient(IPAddress, uint16_t);
    ~MqttClient();

    bool isConnected();
    void reconnect();
    void checkConnection();
};

#endif
#ifndef MQTT_CLIENT_H
#define MQTT_CLIENT_H

#include <WiFi.h>
#include <PubSubClient.h>
#include <Arduino.h>
#include <random>

class MqttClient {
private:
    IPAddress ip;
    uint16_t port;
    byte id[16]; // 16-bytes for client id
    PubSubClient core;
    WiFiClient wifiClient;
    char clientId[6];
    void generateClientId();
public:
    void setup(IPAddress, uint16_t, WiFiClient*);
    bool isConnected();
    bool connect();
    void reconnect();
    void checkConnection();

    bool publish(const char* topic, const char* msg);
};

#endif
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
public:
    char clientId[18];
    void setup(IPAddress, uint16_t, WiFiClient*);
    bool isConnected();
    bool connect();
    bool loop(); 
    bool publish(const char* topic, const char* msg);
};

#endif
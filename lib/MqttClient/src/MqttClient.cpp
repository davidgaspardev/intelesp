#include "MqttClient.h"

void MqttClient::setup(IPAddress ip, uint16_t port, WiFiClient* wifiClient) {
    this->ip = ip;
    this->port = port;
    
    this->core.setClient(*wifiClient);
    this->core.setServer(ip, port);
    this->connect();
}

bool MqttClient::isConnected() {
    return this->core.connected();
}

bool MqttClient::connect() {
    generateClientId();
    bool connectionStatus = this->core.connect(this->clientId);
    
    if(!connectionStatus) {
        Serial.println("[-] (MqttClient) Failed to connect on the broker");
    } else {
        Serial.printf("[+] (MqttClient) Connected on the broker: %s\n", this->clientId);
    }

    return connectionStatus;
}

void MqttClient::reconnect() {
    int k = 0;
    while(!this->isConnected()) {
        Serial.println("Tentando Reconectar MQTT");
        bool isConnected = this->connect();
        k++;
        if(k >= 10) {
            ESP.restart();
        }
    }
}

bool MqttClient::publish(const char* topic, const char* msg) {
    return this->core.publish(topic, msg);
}

void MqttClient::generateClientId() {
    for (int i = 0; i < 5; i++) {
        this->clientId[i] = '0' + random(0, 10);
    }

    this->clientId[5] = '\0';
}
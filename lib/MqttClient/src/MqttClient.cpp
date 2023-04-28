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
    bool connectionStatus = this->core.connect("test", 0, MQTTQOS1, 0, 0);
    
    if(!connectionStatus) {
        Serial.println("[-] (MqttClient) Failed to connect on the broker");
    } else {
        Serial.println("[+] (MqttClient) Connected on the broker");
    }

    return connectionStatus;
}

void MqttClient::reconnect() {
    if(!this->isConnected()) {
        bool isConnected = this->connect();

        if (!isConnected) this->reconnect(); // Try again
    }
}

bool MqttClient::publish(const char* topic, const char* msg) {
    return this->core.publish(topic, msg);
}
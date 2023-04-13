#include "MqttClient.h"

void MqttClient::setup(IPAddress ip, uint16_t port) {
    this->ip = ip;
    this->port = port;
    
    WiFiClient wifiClient;
    this->core.setClient(wifiClient);
    this->core.setServer(ip, port);
}

bool MqttClient::isConnected() {
    return this->core.connected();
}

bool MqttClient::connect() {
    return this->core.connect("test");
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
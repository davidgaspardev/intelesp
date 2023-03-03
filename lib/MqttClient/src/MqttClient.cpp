#include "MqttClient.h"

MqttClient::MqttClient(IPAddress ip, uint16_t port) {
    this->ip = ip;
    this->port = port;
    
    WiFiClient wifiClient;
    this->core.setClient(wifiClient);
    this->core.setServer(ip, port);
}

bool MqttClient::isConnected() {
    return this->core.connected();
}

void MqttClient::reconnect() {
    
}
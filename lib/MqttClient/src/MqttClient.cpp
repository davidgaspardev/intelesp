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
    bool connectionStatus = this->core.connect(this->clientId);

    int timeout_counter = 0;

    while(!connectionStatus) {
        Serial.println("[-] (MqttClient) Failed to connect on the broker");
        delay(1000);
        
        Serial.println("[-] (MqttClient) Trying to connect again");
        connectionStatus = this->core.connect(this->clientId);

        timeout_counter++;
        if(timeout_counter >= 20){
            Serial.println("\n[-] (MqttClient) Error to connect on the Broker, RESTARTING ESP32");
            ESP.restart();
        }
    } 
    
    Serial.printf("[+] (MqttClient) Connected on the broker: %s\n", this->clientId);

    return connectionStatus;
}

bool MqttClient::publish(const char* topic, const char* msg) {
    return this->core.publish(topic, msg);
}

bool MqttClient::loop() {
    return this->core.loop();
}
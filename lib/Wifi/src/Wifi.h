#ifndef WIFI_H
#define WIFI_H

#include <Arduino.h>
#include <WiFi.h>
// #include <String>

class Wifi {
private:
    char ssid[50];
    char pass[50];
public:
    WiFiClient client;
    
    void connect(const char* ssid, const char* pass);
    bool isConnected();
    String macAddress();
};

#endif
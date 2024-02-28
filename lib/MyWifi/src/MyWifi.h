#ifndef _MY_WIFI_H
#define _MY_WIFI_H

#include <Arduino.h>
#include <WiFi.h>
// #include <String>

class MyWifi {
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
#ifndef MY_TIME_H_
#define MY_TIME_H_

#include <time.h>
#include <WiFiUdp.h>
#include <NTPClient.h>

class MyTime {
private:
    WiFiUDP wifiUdp;
    NTPClient nptClient;
    char iso8601[20];
public:
    MyTime();
    void setup();
    char* getISOString(); 
};

#endif
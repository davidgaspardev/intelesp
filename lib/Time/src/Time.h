#ifndef TIME_H_
#define TIME_H_

#include <time.h>
#include <WiFiUdp.h>
#include <NTPClient.h>

class Time {
private:
    WiFiUDP wifiUdp;
    NTPClient nptClient;
    char iso8601[20];
public:
    Time();
    void setup();
    char* getISOString(); 
};

#endif
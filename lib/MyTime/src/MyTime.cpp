#include "MyTime.h"

MyTime::MyTime() : wifiUdp(), nptClient(wifiUdp) {}

void MyTime::setup() {
    nptClient.begin();
    nptClient.setTimeOffset(-10800);
}

char* MyTime::getISOString() {
    this->nptClient.update();
    time_t epoch_time = this->nptClient.getEpochTime();
    struct tm* tm_info = localtime(&epoch_time);
    strftime(this->iso8601, 20, "%Y-%m-%dT%H:%M:%S%z",tm_info);

    return this->iso8601;
}
#include "Time.h"

Time::Time() : wifiUdp(), nptClient(wifiUdp) {}

void Time::setup() {
    nptClient.begin();
}

char* Time::getISOString() {
    this->nptClient.update();

    time_t epoch_time = this->nptClient.getEpochTime();
    struct tm* tm_info = localtime(&epoch_time);
    strftime(this->iso8601, 20, "%Y-%m-%dT%H:%M:%S%z",tm_info);

    return this->iso8601;
}
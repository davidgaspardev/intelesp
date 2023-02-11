#ifndef LED_ONBORAD_H
#define LED_ONBOARD_H

#include <Arduino.h>

class LedOnboard {
public:
    LedOnboard();

    void turnOn();
    void turnOff();
    void blink(uint16_t duration);
};

#endif

#include "LedOnboard.h"

LedOnboard::LedOnboard() {
    pinMode(LED_BUILTIN, OUTPUT);
}

void LedOnboard::turnOn() {
    digitalWrite(LED_BUILTIN, HIGH);
}

void LedOnboard::turnOff() {
    digitalWrite(LED_BUILTIN, LOW);
}

void LedOnboard::blink(uint16_t duration) {
    this->turnOn();
    delay(duration);
    this->turnOff();
}
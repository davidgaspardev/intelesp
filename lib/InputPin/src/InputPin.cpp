#include "InputPin.h"

InputPin::InputPin(uint8_t pinNumber) {
    this->pinNumber = pinNumber;
    this->lastSignal = LOW;

    pinMode(pinNumber, INPUT_PULLDOWN);
}

bool InputPin::signalChanged() {
    this->signal = digitalRead(this->pinNumber);

    return this->signal != this->lastSignal;
}

uint8_t InputPin::getSignal() {
    this->lastSignal = this->signal;

    return this->signal;
}

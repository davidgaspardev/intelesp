#include "InputPin.h"

InputPin::InputPin(uint8_t pinNumber) {
    this->pinNumber = pinNumber;
    pinMode(pinNumber, INPUT_PULLUP);
    
    this->lastSignal = digitalRead(this->pinNumber);
}

bool InputPin::signalChanged() {
    this->signal = digitalRead(this->pinNumber);

    return this->signal != this->lastSignal;
}

uint8_t InputPin::getSignal() {
    this->lastSignal = this->signal;

    return this->signal;
}

uint8_t InputPin::getNumber() {
    return this->pinNumber;
}

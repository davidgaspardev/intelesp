#include "InputPin.h"

InputPin::InputPin(uint8_t pinNumber) {
    this->pinNumber = pinNumber;

    pinMode(pinNumber, INPUT_PULLDOWN);
}

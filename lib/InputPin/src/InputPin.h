#ifndef INPUT_PIN_H
#define INPUT_PIN_H

#include <Arduino.h>

class InputPin {
private:
    uint8_t pinNUmber;
public:
    InputPin(uint8_t pinNumber);
}

#endif

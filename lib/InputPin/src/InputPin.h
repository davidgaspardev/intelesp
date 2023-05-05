#ifndef INPUT_PIN_H
#define INPUT_PIN_H

#include <Arduino.h>

class InputPin {
private:
    uint8_t lastSignal;
    uint8_t signal;
    uint8_t pinNumber;
public:
    InputPin(uint8_t pinNumber);

    bool signalChanged();
    uint8_t getSignal();
    uint8_t getNumber();
};

#endif

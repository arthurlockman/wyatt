#pragma once
#include "Util.h"
#include "Arduino.h"
#include "Hardware.h"

#define FORWARDS 0
#define BACKWARDS 1

class Motor {
public:
    Motor(int forwardPin, int backwardPin);
    void drive(int speed, int direction);

private:
    int forwardPin, backwardPin;   
};
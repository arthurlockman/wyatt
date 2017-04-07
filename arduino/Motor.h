#pragma once
#include "Util.h"
#include "Arduino.h"

#define FORWARDS 0
#define BACKWARDS 1

class Motor {
public:
    Motor(int forwardPin, int backwardPin);
    void drive(double speed, int direction);

private:
    int forwardPin, backwardPin;
    
}
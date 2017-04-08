#pragma once
#include "Arduino.h"

class IRSensor {
public:
    IRSensor(int pin);
    double getDistanceCM();
    
private:
    int pin;
};
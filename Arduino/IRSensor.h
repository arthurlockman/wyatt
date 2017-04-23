#pragma once
#include "Arduino.h"

/* Class to encapsulate the behaivor of an IR sensor */
class IRSensor {
public:
    /* Constructor */
    IRSensor(int pin);

    /* Returns the distance reading in cm */
    double getDistanceCM();
    
private:
    int pin;
};
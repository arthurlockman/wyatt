#pragma once
#include "Util.h"
#include "Arduino.h"
#include "Hardware.h"

#define FORWARDS 0
#define BACKWARDS 1

/*
* Class to encapsulate the behaivor of a single motor 12V Pololu motor.
*/
class Motor {
public:
    /* Constructor */
    Motor(int forwardPin, int backwardPin);

    /*  
    * Drive the motor at a specific speed forwards or backwards
    * speed - A byte value between 0-255 specifying the PWM value to drive the motor at
    * direction - Macro flag specifying forwards or backwards
    */
    void drive(unsigned char speed, int direction);

private:
    int forwardPin, backwardPin;   
};
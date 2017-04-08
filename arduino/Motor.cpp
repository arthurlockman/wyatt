#include "Motor.h"

Motor::Motor(int forwardPin, int backwardPin) {
    this->forwardPin = forwardPin;
    this->backwardPin = backwardPin;

    pinMode(forwardPin, OUTPUT);
    pinMode(backwardPin, OUTPUT);
};

void Motor::drive(int speed, int direction) {
    if(direction == FORWARDS) {
        analogWrite(this->forwardPin, speed);
        analogWrite(this->backwardPin, 0);
    } else if(direction == BACKWARDS) {
        analogWrite(this->backwardPin, speed);
        analogWrite(this->forwardPin, 0);
    }
};


#include "IRSensor.h"

IRSensor::IRSensor(int pin) {
    this->pin = pin;
    pinMode(pin, INPUT);
};

double IRSensor::getDistanceCM() {
    int val = analogRead(this->pin);
    
    double dist = 12343.85 * pow(val, -1.15);
    return dist;
};
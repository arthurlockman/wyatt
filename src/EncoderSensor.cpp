//
// Created by Tucker Haydon on 4/26/17.
//

#include "EncoderSensor.h"

EncoderSensor::EncoderSensor() {
    // Nothing
}

EncoderSensor::~EncoderSensor() {
    // Nothing
}

void EncoderSensor::updateSensor(IMessage *message) {

    if(typeid(*message) != typeid(EncoderMessage)) {
        throw MismatchedMessageException(message);
    }

    // Cast the message
    EncoderMessage* msg = (EncoderMessage*)message;

    // Extract the raw data and multiply by the gear ratio to get the wheel speed
    double rawData = msg->getData();
    this->RPM = rawData * GEAR_RATIO;
}

double EncoderSensor::getRPM() {
    return this->RPM;
}
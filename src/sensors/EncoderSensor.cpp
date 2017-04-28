//
// Created by Tucker Haydon on 4/26/17.
//

#include "sensors/EncoderSensor.h"

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

    this->RPM = msg->getData();
}

double EncoderSensor::getRPM() {
    return this->RPM;
}
//
// Created by Tucker Haydon on 4/25/17.
//

#include "EncoderMessage.h"

EncoderMessage::EncoderMessage(Hardware hardware, double data) : IMessage(hardware) {
    this->data = data;

    if((int)(hardware.messageLength) != sizeof(double)) {
        throw MessageLengthException(hardware);
    }
}

EncoderMessage::~EncoderMessage() {
    // Nothing.
}

double EncoderMessage::getData() {
    return this->data;
}

std::string EncoderMessage::serialize() {
    std::string serial;
    serial.append(1, hardware.address);
    serial.append((char*)(&(this->data)), sizeof(double));
    return serial;
}



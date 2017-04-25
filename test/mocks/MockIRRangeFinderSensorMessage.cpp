//
// Created by Tucker Haydon on 4/25/17.
//

#include "MockIRRangeFinderSensorMessage.h"

MockIRRangeFinderSensorMessage::MockIRRangeFinderSensorMessage(Hardware hardware, std::string data) : IMessage(hardware) {
    this->data = data;
}

MockIRRangeFinderSensorMessage::~MockIRRangeFinderSensorMessage() {
    // Nothing.
}

std::string MockIRRangeFinderSensorMessage::getData() {
    return this->data;
}

std::string MockIRRangeFinderSensorMessage::serialize() {
    std::string serial;
    serial.append(1, hardware.address);
    serial.append((char*)(&(this->data)), 8);
    return serial;
}



#include "MotorMessage.h"


MotorMessage::MotorMessage(Hardware hardware, unsigned char data) : IMessage(hardware) {

    this->data = data;

    // Expect 1 byte
    if((int)(hardware.messageLength) != 1) {
        throw MessageLengthException(hardware);
    }
}

MotorMessage::~MotorMessage() {
    // Nothing.
}

unsigned char MotorMessage::getData() {
    return this->data;
}

std::string MotorMessage::serialize() {
    std::string serial;
    serial.append(1, hardware.address);
    serial.append(1, this->data);
    return serial;
}

#include "MotorMessage.h"


MotorMessage::MotorMessage(Hardware hardware, int data) : IMessage(hardware) {

    this->data = data;

    if((int)(hardware.messageLength) != sizeof(int)) {
        throw MessageLengthException(hardware);
    }
}

MotorMessage::~MotorMessage() {
    // Nothing.
}

int MotorMessage::getData() {
    return this->data;
}

std::string MotorMessage::serialize() {
    std::string serial;
    serial.append(1, hardware.address);
    serial.append((char*)(&(this->data)), sizeof(int));
    return serial;
}

#include "messages/MotorMessage.h"


MotorMessage::MotorMessage(Hardware hardware, int data) : IMessage(hardware) {

    if((int)(hardware.messageLength) != sizeof(int)) {
        throw MessageLengthException(hardware);
    }

    if(data > FULL_FORWARD || data < FULL_BACKWARD) {
        throw DataSizeException(data);
    }

    this->data = data;
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

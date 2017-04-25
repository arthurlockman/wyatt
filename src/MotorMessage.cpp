#include "MotorMessage.h"

MotorMessage::MotorMessage(Hardware hardware, unsigned char data) : IMessage(hardware) {

    this->data = data;

    // TODO
//    if((int)(hardware.messageLength) != msg.size()) {
//        throw MessageLengthException(hardware, msg);
//    }
}

MotorMessage::~MotorMessage() {
    // TODO
}


unsigned char MotorMessage::getData() {
    return this->data;
}

std::string MotorMessage::serialize() {
    // TODO
//    std::string serial;
//    serial.append(1, hardware.address);
//    serial += msg;
//
//    return serial;
    return std::string("");
}

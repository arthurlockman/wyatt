#include "MotorMessage.h"

MotorMessage::MotorMessage(Hardware hardware, std::string msg) {
    this->hardware = hardware;
    this->msg = msg;

    if((int)(hardware.messageLength) != msg.size()) {
        throw MessageLengthException(hardware, msg);
    }
}


std::string Message::getMessage() {
    return this->msg;
}

std::string Message::serialize() {
    std::string serial;
    serial.append(1, hardware.address);
    serial += msg;

    return serial;
}

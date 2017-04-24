#include "Message.h"

Message::Message(Hardware hardware, std::string msg) {
    this->hardware = hardware;
    this->msg = msg;

    if((int)(hardware.messageLength) != msg.size()) {
        throw MessageLengthException(hardware, msg);
    }
}

Message::~Message() {
    // No op
}

Hardware Message::getHardware() {
    return this->hardware;
}

std::string Message::getMessage() {
    return this->msg;
}

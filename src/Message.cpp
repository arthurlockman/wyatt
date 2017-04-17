#include "Message.h"

Message::Message(Hardware hardware, unsigned char* msg) {
    this->hardware = hardware;
    this->msg = msg;
}

Message::~Message() {
    // TODO
    // Free/Delete msg
}

Hardware Message::getHardware() {
    return this->hardware;
}

unsigned char* Message::getMessage() {
    return this->msg;
}

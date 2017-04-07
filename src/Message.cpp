#include "Message.h"

Message::Message(Hardware hardware, char* msg) {
    this->hardware = hardware;
    this->msg = msg;
}

Hardware Message::getHardware() {
    return this->hardware;
}

char* Message::getMessage() {
    return this->msg;
}

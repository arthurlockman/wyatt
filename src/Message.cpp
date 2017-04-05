#include "Message.h"

Message::Message(Hardware hardware, string msg) {
    this->hardware = hardware;
    this->msg = msg;
}

Hardware Message::getHardware() {
    return this->hardware;
}

string Message::getMessage() {
    return this->msg;
}

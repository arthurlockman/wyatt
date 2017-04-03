#include "Message.h"

Message::Message(Hardward hardware, string msg) {
    this->hardware = hardware;
    this->msg = msg;
}

Hardware Message::getHardware() {
    return this->hardware;
}

string Message::write() {
    return this->msg;
}
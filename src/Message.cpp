#include "Message.h"

Message::Message(string msg) {
    this->msg = msg;
}

string Message::write() {
    return this->msg;
}
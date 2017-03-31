#include "Message.h"

Message::message(string msg) {
    this->msg = msg;
}

string Message::write() {
    return this->msg;
}
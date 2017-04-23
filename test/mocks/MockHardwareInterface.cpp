//
// Created by Tucker Haydon on 4/21/17.
//

#include "include/MockHardwareInterface.h"

MockHardwareInterface::MockHardwareInterface() {}

void MockHardwareInterface::write(Message* msg) {
    this->writeMessage = msg;
}

std::list<Message*>* MockHardwareInterface::read() {
    return this->readMessages;
}

void MockHardwareInterface::setReadMessages(std::list<Message*>* messages) {
    this->readMessages = messages;
}

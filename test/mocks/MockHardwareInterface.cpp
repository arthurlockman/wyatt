//
// Created by Tucker Haydon on 4/21/17.
//

#include "include/MockHardwareInterface.h"

MockHardwareInterface::MockHardwareInterface() {}

void MockHardwareInterface::write(IMessage* msg) {
    this->writeMessage = msg;
}

std::list<IMessage*>* MockHardwareInterface::read() {
    return this->readMessages;
}

void MockHardwareInterface::setReadMessages(std::list<IMessage*>* messages) {
    this->readMessages = messages;
}

//
// Created by Tucker Haydon on 4/21/17.
//

#include "include/MockHardwareInterface.h"
#include <iostream>

MockHardwareInterface::MockHardwareInterface() {
    this->writeMessages = new std::list<IMessage*>;
    this->isSet = 0;
}

void MockHardwareInterface::write(IMessage* msg) {
    this->writeMessages->push_back(msg);
}

std::list<IMessage*>* MockHardwareInterface::read() {
    if(this->isSet == 0) {
        return new std::list<IMessage*>;
    } else {
        isSet = 0;
        return this->readMessages;
    }
}

void MockHardwareInterface::setReadMessages(std::list<IMessage*>* messages) {
    this->isSet = 1;
    this->readMessages = messages;
}

std::list<IMessage*>* MockHardwareInterface::getWriteMessages(){
    if(this->writeMessages == NULL) {
        return new std::list<IMessage*>;
    } else {
        return this->writeMessages;
    }
}

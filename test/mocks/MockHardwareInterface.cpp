//
// Created by Tucker Haydon on 4/21/17.
//

#include "include/MockHardwareInterface.h"
#include <iostream>

MockHardwareInterface::MockHardwareInterface() {
    this->writeMessages = new std::list<Message*>;
    this->isSet = 0;
}

void MockHardwareInterface::write(Message* msg) {
    this->writeMessages->push_back(msg);
}

std::list<Message*>* MockHardwareInterface::read() {
    if(this->isSet == 0) {
        return new std::list<Message*>;
    } else {
        isSet = 0;
        return this->readMessages;
    }
}

void MockHardwareInterface::setReadMessages(std::list<Message*>* messages) {
    this->isSet = 1;
    this->readMessages = messages;
}

std::list<Message*>* MockHardwareInterface::getWriteMessages(){
    if(this->writeMessages == NULL) {
        return new std::list<Message*>;
    } else {
        return this->writeMessages;
    }
}

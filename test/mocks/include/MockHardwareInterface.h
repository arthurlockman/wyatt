//
// Created by Tucker Haydon on 4/21/17.
//

#pragma once
#include "hardwareinterface/IHardwareInterface.h"
#include "messages/IMessage.h"
#include <list>

/**
 * Mock class for a hardware interface that can have hardware messages injected and logs the messages written to it.
 */
class MockHardwareInterface : public IHardwareInterface {
public:
    MockHardwareInterface();
    void write(IMessage* msg);
    std::list<IMessage*>* read();
    void setReadMessages(std::list<IMessage*>* messages);
    std::list<IMessage*>* getWriteMessages();

private:
    std::list<IMessage*>* writeMessages;
    std::list<IMessage*>* readMessages;
    int isSet;
};




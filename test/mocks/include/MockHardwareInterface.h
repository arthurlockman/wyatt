//
// Created by Tucker Haydon on 4/21/17.
//

#pragma once
#include "../../../include/IHardwareInterface.h"
#include "../../../include/IMessage.h"
#include <list>


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




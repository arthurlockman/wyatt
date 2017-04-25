//
// Created by Tucker Haydon on 4/21/17.
//

#pragma once
#include "../../../include/IHardwareInterface.h"
#include "../../../include/Message.h"
#include <list>


class MockHardwareInterface : public IHardwareInterface {
public:
    MockHardwareInterface();
    void write(Message* msg);
    std::list<Message*>* read();
    void setReadMessages(std::list<Message*>* messages);

    std::list<Message*>* getWriteMessages();

private:
    std::list<Message*>* writeMessages;
    std::list<Message*>* readMessages;
    int isSet;
};




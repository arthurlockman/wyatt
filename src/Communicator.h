#pragma once

#include <string>
#include <queue>
#include "Message.h"
#include <iostream>

class Communicator {

public:
    Communicator(ISensorManager* sensorManager);
    bool attachArduino(string comPort);
    void queueMsg(Message* msg);


private:
    void sendNextMsg();
    void readData();

    std::queue<Message*>* outBuffer;
    ISensorManager* sensorManager;
}
#pragma once

#include <string>
#include <queue>
#include "Message.h"
#include "ISensorManager.h"
#include <iostream>

using namespace std;

class Communicator {

public:
    Communicator(ISensorManager* sensorManager);
    bool attachArduino(string comPort);
    void queueMsg(Message* msg);    
    void sendNextMsg();
    void readData();

private:
    queue<Message*>* outBuffer;
    ISensorManager* sensorManager;

};
#pragma once

#include <string>
#include <queue>
#include "Message.h"

class Communicator {

public:
    Communicator(ISensorManager* sensorManager);
    bool attachArduino(string comPort);
    void sendData();
    void readData();

private:
    std::queue<Message>* outBuffer;
    ISensorManager* sensorManager;
}
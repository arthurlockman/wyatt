#pragma once

#include <string>
#include <queue>
#include <map>
#include "Message.h"
#include "ISensorManager.h"
#include "Hardware.h"
#include <iostream>

using namespace std;

class Communicator {

public:
    Communicator(ISensorManager* sensorManager);
    bool attachArduino(string comPort, Hardware hardware_target);
    void queueMsg(Message* msg);    
    void sendNextMsg();
    void readData();

private:
    queue<Message*>* outBuffer;
    ISensorManager* sensorManager;

    map<Hardware, string> *hardware_map; 
    map<Hardware, queue<Message*>*> *msg_queue_map; 

};

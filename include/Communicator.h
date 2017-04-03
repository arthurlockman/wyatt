#pragma once

#include <string>
#include <queue>
#include "Message.h"
#include "ISensorManager.h"
#include <iostream>

/*
This class manages data communication between the raspberry pi and the various arduinos on the robot. Upon creation an ISensorManager object must be injected into the class. Then, arduinos must be attached to the various serial communication ports on the raspberry pi. Each arduino manages various hardware components. These components must be specified when attaching an arduino.

To communicate with the hardware, the queueMsg() function is exposed.

To read data from the hardware, the readData() function is exposed. Data read from the sensors should be immedietly passed to the ISensorManager.
*/
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

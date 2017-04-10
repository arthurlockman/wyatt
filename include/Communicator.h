#pragma once

#include <string>
#include <queue>
#include <map>
#include <iostream>
#include <fstream>

#include "Message.h"
#include "ISensorManager.h"
#include "Hardware.h"
#include "SerialPort.h"
#include "CommunicationException.h"
#include "Thread.h"

/* Variables for serial communication */

/*
This class manages data communication between the raspberry pi and the various arduinos on the robot. Upon creation an ISensorManager object must be injected into the class. Then, arduinos must be attached to the various serial communication ports on the raspberry pi. Each arduino manages various hardware components. These components must be specified when attaching an arduino.

To communicate with the hardware, the queueMsg() function is exposed.

To read data from the hardware, the readData() function is exposed. Data read from the sensors should be immedietly passed to the ISensorManager.
*/
class Communicator : public Thread {

public:
    Communicator(ISensorManager* sensorManager, int baudRate);
    ~Communicator();
    void attachHardware(std::string comPort, Hardware hardwareTarget);
//    void attachHardware(std::string comPort, std::list<Hardware>* hardwareTargets);
    void queueMessage(Message* message);
//    void queueMessages(std::list<Message*>* messages);
    void sendNextMsg(Hardware hardwareTarget);
    void writeData();
    void readData();

    void* run() override;

private:
    ISensorManager* sensorManager;
    std::map<Hardware, std::string>* hardwareToSerialPortPathMap; 
    std::map<Hardware, std::queue<Message*>*>* hardwareToMessageQueueMap; 
    std::map<Hardware, SerialPort*>* hardwareToSerialPortMap;
    int baudRate;
};

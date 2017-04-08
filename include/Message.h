#pragma once
#include "Hardware.h"

/*
* This class encapsulates information needed to communicate with various pieces of hardware on a robot. 
* Each message identifies the hardware it is destined for and contains a char array representing the message
*/
class Message {

public:
    /* Constructor */
    Message(Hardware hardware, char* msg);

    /* Returns the char array representing the message */
    char* getMessage();

    /* Returns the hardware the message is destined for */
    Hardware getHardware();

private:
    char* msg;
    Hardware hardware;
};

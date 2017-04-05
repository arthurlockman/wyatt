#pragma once

#include <string>
#include <cstdint>
#include "Hardware.h"

/*
This class encapsulates information needed to communicate with various pieces of hardware on a robot. Each message must have an identifier for the piece of hardware the message is destined and a string representing the data to be sent to the hardware.
*/
using namespace std;
class Message {

public:
    Message(Hardware hardware, string msg);
    string getMessage();
    Hardware getHardware();

private:
    string msg;
    Hardware hardware;
};

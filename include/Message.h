#pragma once

#include <string>
#include <cstdint>
#include "Hardware.h"

using namespace std;

class Message {

public:
    Message(Hardware hardware, string msg);
    string write();
    Hardware getHardware();

private:
    string msg;
    Hardware hardware;
};
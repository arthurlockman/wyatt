
#pragma once
#include "Hardware.h"
#include <string>

template <class T>
class IMessage {

public:

    IMessage(Hardware hardware) {
        this->hardware = hardware;
    }

    virtual ~IMessage() {};

    Hardware getHardware() {
    	return this->hardware;
	}

    virtual std::string serialize() = 0;

    virtual T getData() = 0;

protected:
    Hardware hardware;
};
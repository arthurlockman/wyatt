#pragma once
#include "IMessage.h"

class MotorMessage: public IMessage<unsigned char> {

public:

    MotorMessage(Hardware hardware, unsigned char data);

    ~MotorMessage() override;

    unsigned char getData() override;

    std::string serialize() override;

private:
   	unsigned char data;
};
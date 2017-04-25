//
// Created by Tucker Haydon on 4/25/17.
//

#pragma once
#include "../../include/IMessage.h"
#include <string>




class MockIRRangeFinderSensorMessage: public IMessage {
public:
    MockIRRangeFinderSensorMessage(Hardware hardware, std::string data);
    ~MockIRRangeFinderSensorMessage() override;
    std::string serialize() override;
    std::string getData();

private:
    std::string data;
};
//
// Created by Tucker Haydon on 4/25/17.
//

#pragma once
#include "messages/IMessage.h"
#include <string>

/**
 * Mock message for the MockIRRangeFinderSensor. Required to use the SensorManager with the MockIRRangeFinderSensor.
 */
class MockIRRangeFinderSensorMessage: public IMessage {
public:
    MockIRRangeFinderSensorMessage(Hardware hardware, std::string data);
    ~MockIRRangeFinderSensorMessage() override;
    std::string serialize() override;
    std::string getData();

private:
    std::string data;
};
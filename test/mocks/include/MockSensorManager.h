//
// Created by Tucker Haydon on 4/9/17.
//
#pragma once
#include "sensors/ISensorManager.h"
#include "sensors/ISensor.h"
#include "../../include/Hardware.h"
#include "messages/IMessage.h"
#include <list>

/**
 * Mock SensorManager class that logs what messages are sent to it through updateMessages()
 */
class MockSensorManager : public ISensorManager{

public:
    MockSensorManager();
    ~MockSensorManager() override;
    void addSensor(Hardware hardware, ISensor* sensor) override;
    void updateSensors(std::list<IMessage*>* messages) override;
  
    std::list<IMessage*>* getUpdateMessages();
    std::list<IMessage*>* updateMessages;
};



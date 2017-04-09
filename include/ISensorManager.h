#pragma once

#include <list>
#include "Hardware.h"
#include "ISensor.h"
#include "Message.h"
#include "ISensorManagerExceptions.h"

class ISensorManager{

public:
    virtual ~ISensorManager() {};
    virtual void addSensor(Hardware hardware, ISensor* sensor) = 0;
    virtual void updateSensors(std::list<Message*>* messages) = 0;
};

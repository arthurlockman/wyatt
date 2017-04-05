#pragma once
#include "RawSensorData.h"

class ISensor {

public:
    virtual void updateSensor(RawSensorData* data) = 0;
    virtual ~ISensor() {};
};

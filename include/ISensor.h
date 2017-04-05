#pragma once

class ISensor {

public:
    virtual void updateSensor() = 0;
    virtual ~ISensor() {};
};

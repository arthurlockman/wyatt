#pragma once
#include <list>
#include <ISensor.h>

using namespace std;
class ISensorManager{

public:
    ISensorManager(list<ISensor*>* sensors) {
        this->sensors = sensors;
    };

    virtual ~ISensorManager() = 0;

    virtual void updateSensors() = 0;

protected:
    list<ISensor*>* sensors;
};

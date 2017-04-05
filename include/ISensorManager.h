#pragma once
#include <list>
#include <map>
#include "Hardware.h"
#include "ISensor.h"
#include "Message.h"

using namespace std;
class ISensorManager{

public:

    ISensorManager(map<Hardware, ISensor*>* sensorMap) {
        this->sensorMap = sensorMap;
    };
    virtual ~ISensorManager() {};
    virtual void updateSensors(list<Message*>* messages) = 0;

protected:
    map<Hardware, ISensor*>* sensorMap;
};

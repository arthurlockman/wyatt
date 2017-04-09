#pragma once
#include "ISensorManager.h"
#include "ISensor.h"
#include <list>
#include <map>
#include "Hardware.h"
#include "Message.h"

class SensorManager : public ISensorManager {

    public:
        SensorManager();
        ~SensorManager() override;

        void addSensor(Hardware hardware, ISensor* sensor) override;
        void updateSensors(std::list<Message*>* messages) override;

    private:
        std::map<Hardware, ISensor*>* sensorMap;
};

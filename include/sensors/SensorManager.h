#pragma once
#include "sensors/ISensorManager.h"
#include "sensors/ISensor.h"
#include <list>
#include <map>
#include "Hardware.h"
#include "messages/IMessage.h"
#include <iostream>
#include "exceptions/NonexistentHardwareException.h"
#include "exceptions/DuplicateHardwareException.h"

/**
 * Implementation header of ISensorManager.
 */
class SensorManager : public ISensorManager {
public:
    /**
     * Constructor.
     */
    SensorManager();

    /**
     * Destructor. Must override. Deletes all pointers.
     */
    ~SensorManager() override;

    /**
     * Adds a sensor to be managed
     * @param hardware The hardware struct associated with the sensor object
     * @param sensor An ISensor object to manage
     */
    void addSensor(Hardware hardware, ISensor* sensor) override;

    /**
     * Updates sensors with new measurement data
     * @param messages A list of messages containing new measurement data
     */
    void updateSensors(std::list<IMessage*>* messages) override;

private:
    std::map<Hardware, ISensor*>* sensorMap;
};

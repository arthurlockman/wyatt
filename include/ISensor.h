#pragma once
#include "IMessage.h"

/**
 * Interface for all sensors
 */
class ISensor {
public:

    /**
     * Update sensor data from a new measurement
     * @param data RawSensorData from a new measurement. Should delete pointer.
     */
    virtual void updateSensor(IMessage* message) = 0;

    /**
     * Deconstructor. Should delete all pointers.
     */
    virtual ~ISensor() {};
};

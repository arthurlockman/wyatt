#pragma once
#include "RawSensorData.h"

/**
 * Interface for all sensors
 */
class ISensor {
public:

    /**
     * Update sensor data from a new measurement
     * @param data RawSensorData from a new measurement. Should delete pointer.
     */
    virtual void updateSensor(RawSensorData* data) = 0;

    /**
     * Deconstructor. Should delete all pointers.
     */
    virtual ~ISensor() {};
};

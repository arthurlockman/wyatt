#pragma once
#include "messages/IMessage.h"

/**
 * Interface for all sensors. All sensors must expose a method to update them.
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

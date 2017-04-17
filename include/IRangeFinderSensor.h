#pragma once
#include "ISensor.h"

/**
 * Interface for range finding sensors.
 */
class IRangeFinderSensor : public ISensor {

public:
    /**
     * Deconstructor. Deletes all pointer references.
     */
    virtual ~IRangeFinderSensor() override {};

    /**
     * Update this sensor object with data received from a peripheral. Deletes data upon completion.
     * @param data The data received from the peripheral.
     */
    virtual void updateSensor(RawSensorData* data) override = 0;

    /**
     * Returns the most recent distance reading in centimeters.
     * @return The most recent distance reading in centimeters.
     */
    virtual double getDistanceCM() = 0;
};

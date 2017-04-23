#pragma once

#include <list>
#include "Hardware.h"
#include "ISensor.h"
#include "Message.h"
#include "ISensorManagerExceptions.h"

/**
 * Class for managing sensor data. Receives sensor data from the updateSensors function and writes the data to the respective sensors.
 */
class ISensorManager{

public:
    /**
     * Destructor. Deletes pointer references.
     */
    virtual ~ISensorManager() {};

    /**
     * Adds a sensor to be managed
     * @param hardware The Hardware type of the sensor
     * @param sensor A pointer to the ISensor object
     */
    virtual void addSensor(Hardware hardware, ISensor* sensor) = 0;

    /**
     * Receives data and distributes it to the respective sensors. Deletes the messages upon completion.
     * @param messages A list of Messages
     */
    virtual void updateSensors(std::list<Message*>* messages) = 0;
};

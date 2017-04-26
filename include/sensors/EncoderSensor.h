//
// Created by Tucker Haydon on 4/26/17.
//

#pragma once

#include "messages/IMessage.h"
#include "ISensor.h"
#include "exceptions/MismatchedMessageException.h"
#include <typeinfo>
#include "messages/EncoderMessage.h"

#define GEAR_RATIO ((double) 1/19.0 * 3.0/5.0)


/**
 * Model class used to encapsulate the current state of an encoder.
 */
class EncoderSensor: public ISensor {

public:
    /**
     * Constructor.
     */
    EncoderSensor();

    /**
     * Destructor.
     */
    ~EncoderSensor();

    /**
     * Updates this object with the newest measurements from an encoder. Measurements may need to be scaled by a gear ratio.
     * @param message IMessage (EncoderMessage) encapsulating the newest measurements.
     * @throws MismatchedMessageException if the type of the message is not EncoderMessage
     */
    void updateSensor(IMessage* message);

    /**
     * Returns the RPM of a wheel.
     * @return
     */
    double getRPM();

private:
    /**
     * The current RPM of a wheel
     */
    double RPM;
};
//
// Created by Tucker Haydon on 4/25/17.
//

#pragma once

#include "messages/IMessage.h"
#include "Hardware.h"
#include <string>

/**
 * Message class encapsulating data between the raspi and the pololu motor encoders. The Double data represents the RPM of the motor. It may need to be scaled depending on the gear ratio.
 * TODO: to decouple the program from the hardware, the data should represent the speed of the motors in cm/s instead of rpm.
 */
class EncoderMessage: public IMessage {
public:
    /**
     * Constructor.
     * @param hardware The hardware address for the encoder
     * @param data Double representing the RPM speed of the motors
     * @throws MessageLengthException if hardware length does not match the data size
     */
    EncoderMessage(Hardware hardware, double data);

    /**
     * Destructor.
     */
    ~EncoderMessage() override;

    /**
     * Serializes the message into a string representation. The hardware address is appended to the front.
     * @return A string representation of the message.
     */
    std::string serialize() override;

    /**
     * Returns the double data the message is encapsulating
     * @return Double data the message is encapsulating.
     */
    double getData();

private:
    /**
     * Double data representing the RPM speed of a motor. Speed may need to be scaled by gear ratio.
     */
    double data;
};




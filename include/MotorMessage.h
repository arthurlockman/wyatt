#pragma once
#include "IMessage.h"

/**
 * Message class encapsulating data sent to the Pololu motors.
 */
class MotorMessage: public IMessage {

public:

    /**
     * Constructor
     * @param hardware The hardware address of the motor
     * @param data An unsigned character representing the speed of the motor [0-255] -> [Backwards(0)-Forwards(255)]
     * @throws MessageLengthException if the data is not the correct length
     */
    MotorMessage(Hardware hardware, unsigned char data);

    /**
     * Destructor
     */
    ~MotorMessage() override;

    /**
     * Returns the data the message is encapsulating.
     * @return Data for the motor
     */
    unsigned char getData();

    /**
     * Serializes the message into a string representation. The hardware address is appended to the front.
     * @return A string representation of the message.
     */
    std::string serialize() override;

private:
    /**
     * Unsigned character representing the speed of the motor [0-255] -> [Backwards(0)-Forwards(255)]
     */
   	unsigned char data;
};
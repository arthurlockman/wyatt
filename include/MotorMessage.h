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
     * @param data An Integer representing the speed of the motor [-4095 - 4095] = [Full Backwards, Full Forwards]
     * @throws MessageLengthException if the data is not the correct length
     */
    MotorMessage(Hardware hardware, int data);

    /**
     * Destructor
     */
    ~MotorMessage() override;

    /**
     * Serializes the message into a string representation. The hardware address is appended to the front.
     * @return A string representation of the message.
     */
    std::string serialize() override;

    /**
    * Returns the data the message is encapsulating.
    * @return Data for the motor
    */
    int getData();

private:
    /**
     * Integer representing the speed of the motor [-4095 - 4095] = [Full Backwards, Full Forwards]
     */
   	int data;
};
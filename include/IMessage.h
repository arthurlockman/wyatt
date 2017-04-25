
#pragma once
#include "Hardware.h"
#include <string>
#include "MessageLengthException.h"

/**
 * Message interface. All messages are required to state the hardware they are sent to/come from. In addition, they must all serialize themselves into string format.
 */
class IMessage {
public:

    /**
     * Constructor.
     * @param hardware The hardware the message is destined to/coming from.
     */
    IMessage(Hardware hardware) {
        this->hardware = hardware;
    }

    /**
     * Destructor.
     */
    virtual ~IMessage() {};

    /**
     * Returns the hardware associated with the message
     * @return Hardware associated with the message
     */
    Hardware getHardware() {
    	return this->hardware;
	}

    /**
     * Serialize the message as a string. The hardware address is appended to the front of the string.
     * @return A string representation of the message.
     */
    virtual std::string serialize() = 0;


protected:
    /**
     * Hardware associated with the message
     */
    Hardware hardware;
};
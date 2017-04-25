#pragma once
#include "Hardware.h"
#include <string>
#include "MessageLengthException.h"

/**
 * This class encapsulates information transmitted between the Raspi and a peripheral.
 */
class Message {

public:
    /**
     * Constructor.
     * @param hardware The hardware this came from/goes to.
     * @param msg An byte array of data
     * @throws MismatchedHardwareException if hardware message length doesnt match message length.
     */
    Message(Hardware hardware, std::string msg);

    /**
     * Deconstructor. Deletes all object references.
     */
    ~Message();

    /**
     * Returns a string representation of data.
     * @return
     */
    std::string getMessage();

    /**
     * Returns the hardware that this message came from/goes to. This hardware maintains the length of the message in bytes.
     * @return The hardware that this message came from/goes to.
     */
    Hardware getHardware();

    /**
     * Serializes object as a string. Appends the hardware address as a character to the front of the data.
     * @return A string representation of this object.
     */
    std::string serialize();

private:
    std::string msg;
    Hardware hardware;
};


#pragma once
#include "Hardware.h"
#include <string>



/**
 * Custom exception thrown when a message is composed with the wrong length of data
 */
class MessageLengthException: public std::exception {

public:
    MessageLengthException(Hardware h, std::string data) : std::exception() {
        this->data = data;
        this->hardware = hardware;
    }

    virtual const char* what() const throw() {
        std::string msg("Message length does not match hardware description.\n");
        msg += "Hardware address: ";
        msg += (int)hardware.address;
        msg += "\nData: ";
        msg += data;
        return msg.c_str();
    }

private:
    std::string data;
    Hardware hardware;
};

/**
 * This class encapsulates information transmitted between the Raspi and a peripheral.
 */
class IMessage {

public:

    /**
     * Deconstructor. Deletes all object references.
     */
    virtual ~IMessage();


    /**
     * Returns the hardware that this message came from/goes to. This hardware maintains the length of the message in bytes.
     * @return The hardware that this message came from/goes to.
     */
    Hardware Message::getHardware() {
    	return this->hardware;
	}

    /**
     * Serializes object as a string. Appends the hardware address as a character to the front of the data.
     * @return A string representation of this object.
     */
    virtual std::string serialize();

protected:
    Hardware hardware;
};
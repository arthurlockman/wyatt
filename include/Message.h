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

private:
    std::string msg;
    Hardware hardware;
};

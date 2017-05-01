//
// Created by Tucker Haydon on 4/25/17.
//

#pragma once

#include "Hardware.h"
#include <string>

/**
 * Custom exception thrown when a message is composed with the wrong length of data
 */
class MessageLengthException: public std::exception {

public:
    /**
     * Constructor
     * @param h The Hardware requiring a specific length in bytes of data
     */
    MessageLengthException(Hardware h) : std::exception() {
        this->hardware = hardware;
    }

    /**
    * Returns a message describing what went wrong.
    * @return A char pointer to a message of what went wrong.
    */
    virtual const char* what() const throw() {
        std::string msg("Message length does not match hardware description.\n");
        msg += "Hardware address: ";
        msg += (int)hardware.address;
        return msg.c_str();
    }

private:
    Hardware hardware;
};


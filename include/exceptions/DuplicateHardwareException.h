//
// Created by Tucker Haydon on 4/24/17.
//

#pragma once

/**
 * Custom exception thrown when trying to attach a duplicate piece of hardware.
 */
class DuplicateHardwareException: public std::exception {

public:
    DuplicateHardwareException(Hardware hardware) : std::exception() {
        this->hardware = hardware;
    }

    virtual const char* what() const throw() {
        std::string msg("Hardware has already been added. Address: ");
        msg += (int)((this->hardware).address);
        msg += "\nLength: ";
        msg += (int)((this->hardware).messageLength);
        return msg.c_str();
    }

private:
    Hardware hardware;
};
//
// Created by Tucker Haydon on 4/24/17.
//

#pragma once

/**
 * Custom exception thrown when trying to update hardware that has not been attached.
 */
class NonexistentHardwareException: public std::exception {

public:
    NonexistentHardwareException(Hardware hardware) : std::exception() {
        this->hardware = hardware;
    }

    virtual const char* what() const throw() {
        std::string msg("Hardware does not exist. Address: ");
        msg += (int)((this->hardware).address);
        msg += "\nLength: ";
        msg += (int)((this->hardware).messageLength);
        return msg.c_str();
    }

private:
    Hardware hardware;
};
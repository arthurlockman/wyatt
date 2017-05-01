//
// Created by Tucker Haydon on 4/24/17.
//

#pragma once

/**
 * Custom exception thrown when trying to update hardware that had not been registered with an object.
 */
class NonexistentHardwareException: public std::exception {

public:
    /**
     * Constructor.
     * @param hardware The unregistered hardware struct
     */
    NonexistentHardwareException(Hardware hardware) : std::exception() {
        this->hardware = hardware;
    }

    /**
    * Returns a message describing what went wrong.
    * @return A char pointer to a message of what went wrong.
    */
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
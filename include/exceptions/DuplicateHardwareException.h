//
// Created by Tucker Haydon on 4/24/17.
//

#pragma once

/**
 * Custom exception thrown when trying to register a duplicate piece of hardware with an object. See Communicator.
 */
class DuplicateHardwareException: public std::exception {

public:
    /**
     * Constructor.
     * @param hardware The duplicate piece of hardware
     */
    DuplicateHardwareException(Hardware hardware) : std::exception() {
        this->hardware = hardware;
    }

    /**
    * Returns a message describing what went wrong.
    * @return A char pointer to a message of what went wrong.
    */
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
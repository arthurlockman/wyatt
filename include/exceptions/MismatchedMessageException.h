//
// Created by Tucker Haydon on 4/26/17.
//

#pragma once

#include "messages/IMessage.h"
#include <typeinfo>

/**
 * Custom exception thrown when a message of the wrong type is passed to an object.
 */
class MismatchedMessageException: public std::exception {

public:
    /**
     * Constructor.
     * @param msg The Message passed to the object that throws this exception
     */
    MismatchedMessageException(IMessage* msg): std::exception() {
        this->msg = msg;
    }

    /**
    * Returns a message describing what went wrong.
    * @return A char pointer to a message of what went wrong.
    */
    virtual const char* what() const throw() {
        std::string msg("Message is of wrong type: ");
        msg += typeid(this->msg).name();
        return msg.c_str();
    }

private:
    IMessage* msg;
};
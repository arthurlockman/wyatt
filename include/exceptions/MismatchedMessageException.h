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
    MismatchedMessageException(IMessage* msg): std::exception() {
        this->msg = msg;
    }

    virtual const char* what() const throw() {
        std::string msg("Message is of wrong type: ");
        msg += typeid(this->msg).name();
        return msg.c_str();
    }

private:
    IMessage* msg;
};
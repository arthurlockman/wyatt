//
// Created by Tucker Haydon on 4/17/17.
//

#pragma once
#include "messages/IMessage.h"
#include <list>

/**
 * Interface that describes what functions hardware adapters should expose to the rest of the program.
 */
class IHardwareInterface {
public:
    /**
     * Deconstructor. Delete any pointer references.
     */
    virtual ~IHardwareInterface() {};

    /**
     * Write a message to the peripheral. Deletes the message pointer.
     * @param msg A Message to be sent
     */
    virtual void write(IMessage* msg) = 0;

    /**
     * Read data from the peripheral
     * @return A list of Messages
     */
    virtual std::list<IMessage*>* read() = 0;
};

//
// Created by Tucker Haydon on 4/17/17.
//

#pragma once
#include "IMessage.h"
#include <list>

/**
 * Class for managing hardware interface between Raspi and a peripheral. Any implementing classes must expose read and write functions. Read must return a list of Messages and write must write a single message to the peripheral.
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

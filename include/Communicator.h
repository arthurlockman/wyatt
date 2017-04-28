#pragma once

#include <string>
#include <queue>
#include <map>
#include <iostream>
#include <fstream>

#include "messages/IMessage.h"
#include "sensors/ISensorManager.h"
#include "Hardware.h"
#include "Thread.h"
#include "hardwareinterface/IHardwareInterface.h"
#include "exceptions/DuplicateHardwareException.h"

/**
 * Class that oversees communication between the Raspberry pi and a single peripheral. Data that is read/written to/from a peripheral must pass through this class. This class runs on its own thread and exposes functions to queue messages.
 *
 * Data read from the peripheral is immediately passed to the ISensorManager object for handing.
 */
class Communicator : public Thread {

public:
    /**
    * Constructor.
    * @param sensorManager The ISensorManager object to pass data to.
    */
    Communicator(ISensorManager* sensorManager);

    /**
    * Deconstructor. Deletes all pointer references.
    */
    ~Communicator();

    /**
     * Registers a piece of hardware with the communicator
     * @param hardware The hardware to register
     * @param interface The interface from which to read/write messages to the hardware
     * @throws DuplicateHardwareException Thrown when hardware is registered more than once.
     */
    void registerHardware(Hardware hardware, IHardwareInterface* interface);

    /**
    * Add a message to a queue to be written to the peripheral
    * @param msg A Message object to be written
    */
    void queueMessage(IMessage* message);

    /**
    * Add a list of messages to a queue to be written to the peripheral
    * @param messages An std::list of Messages to be written
    */
    void queueMessage(std::list<IMessage*>* messages);

    /**
    * Overwritten Thread run function. Continuously reads and writes data to the peripheral
    * @return NULL
    */
    void* run() override;

private:
    ISensorManager* sensorManager;
    std::map<Hardware, IMessage*>* messageMap;
    std::map<Hardware, IHardwareInterface*>* hardwareInterfaceMap;
    std::list<IHardwareInterface*>* hardwareInterfaces;

    /**
    * Write all messages in the queue to the peripheral
    */
    void write();

    /**
    * Read all data from the peripheral and pass it to the sensor manager
    */
    void read();

};

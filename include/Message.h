#pragma once
#include "Hardware.h"

/**
 * This class encapsulates information transmitted between the Raspi and a peripheral.
 */
class Message {

public:
    /**
     * Constructor.
     * @param hardware The hardware this came from/goes to.
     * @param msg An byte array of data
     */
    Message(Hardware hardware, unsigned char* msg);

    /**
     * Deconstructor. Deletes all object references.
     */
    ~Message();

    /**
     * Returns a pointer to the byte array. The length of this array is maintained in the Hardware class.
     * @return
     */
    unsigned char* getMessage();

    /**
     * Returns the hardware that this message came from/goes to.
     * @return The hardware that this message came from/goes to.
     */
    Hardware getHardware();

private:
    unsigned char* msg;
    Hardware hardware;
};

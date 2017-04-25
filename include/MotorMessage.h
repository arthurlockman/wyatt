#pragma once
#include "IMessage.h"


class MotorMessage: public IMessage {

public:

	/**
     * Constructor.
     * @param hardware The hardware this came from/goes to.
     * @param msg An byte array of data
     * @throws MismatchedHardwareException if hardware message length doesnt match message length.
     */
    MotorMessage(Hardware hardware, std::string msg);


    /**
     * Deconstructor. Deletes all object references.
     */
    ~MotorMessage();


	/**
     * Returns a string representation of data.
     * @return
     */
    std::string getMessage();


    /**
     * Serializes object as a string. Appends the hardware address as a character to the front of the data.
     * @return A string representation of this object.
     */
    std::string serialize();


private:
   	std::string msg;
};
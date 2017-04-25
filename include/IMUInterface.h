//
// Created by Tucker Haydon on 4/25/17.
//

#pragma once
#define GYRO_ADDRESS 0x6B
#define ACC_MAG_ADDRESS 0x1D

#include "Message.h"
#include <list>
#include "wiringPiInclude.h"


class GyroscopeInterface: public Thread, public IHardwareInterface {

public:
    GyroscopeInterface();

    ~GyroscopeInterface();

    /**
     * Runs the gyroscope polling thread.
     * @return nothing
     */
    void* run() override;

    /**
     * Returns a list of messages containing updates from the gyroscope
     * @return A list of message pointers
     */
    std::list<Message*>* read() override;

    /**
     * No write to the gyroscope allowed.
     * @param message Data to be sent to the gyroscope.
     */
    void write(Message* message) override {};
private:
    int m_i2c;
};




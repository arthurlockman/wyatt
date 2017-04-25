//
// Created by Tucker Haydon on 4/25/17.
//

#include "../include/IMUInterface.h"

class IMUInterface {

    IMUInterface::IMUInterface() {
        this->m_i2c = wiringPiI2CSetup(GYRO_ADDRESS);
    }

    IMUInterface::~IMUInterface() {

    }

    void* IMUInterface::run() {

    }

    std::list<Message*>* IMUInterface::read() {

    }

    void IMUInterface::write(Message* message) {

    }
};


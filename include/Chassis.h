//
// Created by Tucker Haydon on 4/23/17.
//

#pragma once

#include "IHardwareInterface.h"
#include "AdafruitPWMServoHat.h"
#include <list>
#include "Hardware.h"
#include <stdlib.h>
#include <iostream>

class Chassis: public IHardwareInterface {
public:
    Chassis();
    ~Chassis() override;
    void write(Message* msg) override;
    std::list<Message*>* read() override;
private:
    AdafruitPWMServoHat* m_pwmHat;
    enum m_motorAddresses: int {
        right1 = 0,
        right2,
        left1,
        left2
    };
    enum m_motor: int {
        LEFT_MOTOR = 0,
        RIGHT_MOTOR
    };

    void driveMotor(m_motor, int speed);
    int mapMotorSpeed(int speed);
};




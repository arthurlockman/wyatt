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
#include "NonexistentHardwareException.h"

class Chassis: public IHardwareInterface {
public:
    /**
     * Creates a chassis object. This also instantiates
     * the Adafruit PWM Servo Hat module.
     */
    Chassis();
    /**
     * Destructs the chassis module.
     */
    ~Chassis() override;
    /**
     * Send a command to the chassis (a command
     * to drive is expected here).
     * @param msg The drive command message.
     */
    void write(Message* msg) override;
    /**
     * Get messages from the chassis. This will never
     * return a real value, as the chassis does not send
     * any messages.
     * @return NULL.
     */
    std::list<Message*>* read() override;
private:
    //! Instance of the PWM Servo Hat.
    AdafruitPWMServoHat* m_pwmHat;

    /**
     * Enumerates the addresses on the servo hat of
     * each of the pins for the left and right motors.
     */
    enum m_motorAddresses: int {
        right1 = 0,
        right2,
        left1,
        left2
    };

    /**
     * Drives a specific motor at a specific speed.
     * @param speed A value from 0 - 255, motor speed.
     */
    void driveMotor(unsigned char motorAddress, unsigned char speed);

    /**
     * Convert motor speed from 0 - 255 to -4095 - 4095 to hand
     * off to the servo hat.
     * @param speed an unsigned char, 0 - 255.
     * @return a speed, int, -4095 - 4095
     */
    int mapMotorSpeed(unsigned char speed);
};

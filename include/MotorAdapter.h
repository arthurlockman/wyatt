//
// Created by Tucker Haydon on 4/25/17.
//

#pragma once

#include "IHardwareInterface.h"
#include "AdafruitPWMServoHat.h"
#include "IMessage.h"
#include "MotorMessage.h"
#include <stdlib.h>
#include "MismatchedMessageException.h"

/**
 * Adapter class for communicating with Pololu motor hardware.
 */
class MotorAdapter : public IHardwareInterface {
public:

    /**
     * Constructor
     * @param m_pwmHat PAdafruitPWMServoObject used to communicate with motor
     * @param forwardPin Set this pin to PWM to drive motor forward. Set to 0 for backwards.
     * @param backwardPin Set this pin to PWM to drive motor backward. Set to 0 for forward.
     */
    MotorAdapter(AdafruitPWMServoHat* m_pwmHat, int forwardPin, int backwardPin);

    /**
     * Deconstructor.
     */
    ~MotorAdapter() override;

    /**
     * Write a message to the motor. Contains a byte [0-255] specifying motor speed.
     * @param msg A message wrapping a byte specifying motor speed
     * @throws MismatchedMessageException Message is of wrong type
     */
    void write(IMessage* msg) override;

    /**
     * Read data from the motor. Cannot. Returns empty list.
     * @return An empty list of IMessages.
     */
    std::list<IMessage*>* read() override {
        return new std::list<IMessage*>;
    };

private:
    AdafruitPWMServoHat* m_pwmHat;
    int forwardPin, backwardPin;

    /**
     * Drives a specific motor at a specific speed.
     * @param speed A value from 0 - 255, motor speed.
     */
    void driveMotor(unsigned char speed);

    /**
     * Convert motor speed from 0 - 255 to -4095 - 4095 to hand
     * off to the servo hat.
     * @param speed an unsigned char, 0 - 255.
     * @return a speed, int, -4095 - 4095
     */
    int mapMotorSpeed(unsigned char speed);

};
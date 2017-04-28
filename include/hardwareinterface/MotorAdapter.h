//
// Created by Tucker Haydon on 4/25/17.
//

#pragma once

#include "hardwareinterface/IHardwareInterface.h"
#include "hardwareinterface/AdafruitPWMServoHat.h"
#include "messages/IMessage.h"
#include "messages/MotorMessage.h"
#include <stdlib.h>
#include "exceptions/MismatchedMessageException.h"

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
     * Write a message to the motor. Contains an integer representing the speed of the motor [-4095 - 4095] = [Full Backwards, Full Forwards]
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
     * @param speed Integer representing the speed of the motor [-4095 - 4095] = [Full Backwards, Full Forwards]
     */
    void driveMotor(int speed);


};
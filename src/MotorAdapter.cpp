//
// Created by Tucker Haydon on 4/25/17.
//

#include "../include/MotorAdapter.h"

MotorAdapter::MotorAdapter(AdafruitPWMServoHat* m_pwmHat, int forwardPin, int backwardPin) {
    this->m_pwmHat = m_pwmHat;
    this->forwardPin = forwardPin;
    this->backwardPin = backwardPin;
}

MotorAdapter::~MotorAdapter() {
    // Nothing.
}

void MotorAdapter::write(IMessage* m) {

    if(typeid(*m) != typeid(MotorMessage)) {
        throw MismatchedMessageException(m);
    }

    MotorMessage* msg = (MotorMessage*)m;
    unsigned char speed = msg->getData();
    driveMotor(speed);
    delete msg;
}

void MotorAdapter::driveMotor(unsigned char speed) {

    int motorSpeed = mapMotorSpeed(speed);
    if(motorSpeed < 0) {
        m_pwmHat->setMotor(this->forwardPin, abs(motorSpeed));
        m_pwmHat->setMotor(this->backwardPin, 0);
    } else {
        m_pwmHat->setMotor(this->forwardPin, 0);
        m_pwmHat->setMotor(this->backwardPin, abs(motorSpeed));
    }
}

int MotorAdapter::mapMotorSpeed(unsigned char speed) {
    double mappedSpeed = (2 * 4096.0 * ((double)speed)/ 255.0 - 4096.0);
    return (int)mappedSpeed;
}
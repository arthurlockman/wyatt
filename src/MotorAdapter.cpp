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
    int speed = msg->getData();
    driveMotor(speed);
    delete msg;
}

void MotorAdapter::driveMotor(int speed) {

    if(speed < 0) {
        m_pwmHat->setMotor(this->forwardPin, abs(speed));
        m_pwmHat->setMotor(this->backwardPin, 0);
    } else {
        m_pwmHat->setMotor(this->forwardPin, 0);
        m_pwmHat->setMotor(this->backwardPin, abs(speed));
    }
}

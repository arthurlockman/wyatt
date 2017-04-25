//
// Created by Tucker Haydon on 4/23/17.
//

#include "../include/Chassis.h"

Chassis::Chassis() {
    this->m_pwmHat = new AdafruitPWMServoHat();
}

Chassis::~Chassis() {
    delete this->m_pwmHat;
}

void Chassis::write(Message* msg) {

    Hardware hardware = msg->getHardware();
    int messageLength = hardware.messageLength;
    unsigned char data[messageLength];

    for(int i = 0; i < messageLength; i++) {
        data[i] = (unsigned char)msg->getMessage().at(i);
    }

    switch(hardware.address) {
        case RIGHT_MOTOR_ADDRESS:
            driveMotor(RIGHT_MOTOR_ADDRESS, data[0]);
            break;
        case LEFT_MOTOR_ADDRESS:
            driveMotor(LEFT_MOTOR_ADDRESS, data[0]);
            break;
        default:
            throw NonexistentHardwareException(hardware);
    }

    delete msg;
}

void Chassis::driveMotor(unsigned char motorAddress, unsigned char speed) {

    int motorSpeed = mapMotorSpeed(speed);
    switch(motorAddress) {
        case LEFT_MOTOR_ADDRESS:
            if(motorSpeed < 0) {
                m_pwmHat->setMotor(m_motorAddresses::left1, abs(motorSpeed));
                m_pwmHat->setMotor(m_motorAddresses::left2, 0);
            } else {
                m_pwmHat->setMotor(m_motorAddresses::left1, 0);
                m_pwmHat->setMotor(m_motorAddresses::left2, abs(motorSpeed));
            }
            break;
        case RIGHT_MOTOR_ADDRESS:
            if(motorSpeed < 0) {
                m_pwmHat->setMotor(m_motorAddresses::right1, abs(motorSpeed));
                m_pwmHat->setMotor(m_motorAddresses::right2, 0);
            } else {
                m_pwmHat->setMotor(m_motorAddresses::right1, 0);
                m_pwmHat->setMotor(m_motorAddresses::right2, abs(motorSpeed));
            }
            break;
    }
}

int Chassis::mapMotorSpeed(unsigned char speed) {
    double mappedSpeed = (2 * 4096.0 * ((double)speed)/ 255.0 - 4096.0);
    return (int)mappedSpeed;
}

std::list<Message*>* Chassis::read() {
    std::list<Message*>* messages = new std::list<Message*>;
    return messages;
}
